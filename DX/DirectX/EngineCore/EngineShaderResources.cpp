#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"
#include "EngineStructuredBuffer.h"

#include "EngineTexture.h"
#include "EngineSampler.h"

void UEngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == IsConstantBuffer(UpperName))
	{
		MsgBoxAssert("존재하지도 않는 상수 버퍼에 세팅하려고 했습니다." + UpperName);
		return;
	}

	for(std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair:ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (false == ResMap.contains(UpperName))
		{
			continue;
		}
		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (Setter.BufferSize != _Size)
		{
			MsgBoxAssert(Setter.Res->GetName() + "의 바이트 크기가 다릅니다." + std::to_string(Setter.BufferSize) + "Vs" + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for(std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair :ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return true;
		}
	}

	return false;
}

void UEngineShaderResources::SettingTexture(std::string_view _TexName, std::string_view _ImageName, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = UEngineTexture::FindRes(_ImageName);
	SettingTexture(_TexName, FindTexture, _SamperName);
}

void UEngineShaderResources::SettingTexture(std::string_view _TexName, std::shared_ptr<UEngineTexture> _Texture, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = _Texture;
	std::shared_ptr<UEngineSampler> FindSampler = UEngineSampler::FindRes(_SamperName);

	if (nullptr == FindTexture)
	{
		MsgBoxAssert("존재하지 않은 텍스처를 세팅하려고 했습니다.");
		return;
	}

	if (nullptr == FindSampler)
	{
		MsgBoxAssert("존재하지 않는 샘플러를 세팅하려고 했습니다.");
		return;
	}

	std::string UppertName = UEngineString::ToUpper(_TexName);
	std::string SamUpperNmae = UppertName + "_SAMPLER";

	for (std::pair<const EShaderType, std::map<std::string, UEngineTexturSetter>>& Pair : Textures)
	{
		std::map<std::string, UEngineTexturSetter>& TexMap = Pair.second;
		std::map<std::string, UEngineSamplerSetter>& SmpMap = Samplers[Pair.first];

		// 샘플러와 텍스처가 한쌍이 아니면 세팅자제를 하지 않는 구조

		if (false == TexMap.contains(UppertName))
		{
			continue;
		}

		if (false == TexMap.contains(SamUpperNmae))
		{
			continue;
		}

		UEngineTexturSetter& TexSetter = TexMap[UppertName];
		UEngineSamplerSetter& SamSetter = SmpMap[SamUpperNmae];

		TexSetter.Res = FindTexture;
		SamSetter.Res = FindSampler;
	}
	

}

void UEngineShaderResources::ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode)
{
	// _EntryName -> 무슨 쉐이더에 무슨 리소스가 있는지 확인용

	if (nullptr == _ShaderCode)
	{
		MsgBoxAssert("컴파일이 실패한 쉐이더에서 리소스 체크를 하려고 했습니다.");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	// 다이렉트X가 자동검색 기능과 함수를 제공

	// Reflection 

	ID3D11ShaderReflection* CompileInfo = nullptr;

	if (S_OK != D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 정보수집에 실패");
		return;
	}

	D3D11_SHADER_DESC Info = {};

	CompileInfo->GetDesc(&Info);

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC ResDesc;

		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = UEngineString::ToUpper(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 상수버퍼의 세세한 정보를 알려줘
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			_EntryName;

			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);

			UEngineConstantBufferSetter& NewSetter = ConstantBuffers[_Type][UpperName];

			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;
			NewSetter.Res = Buffer;
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			ResDesc.Name;
			UEngineTexturSetter& NewSetter = Textures[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			ResDesc.Name;
			UEngineSamplerSetter& NewSetter = Samplers[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		case D3D_SIT_STRUCTURED:
		{
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};
			BufferInfo->GetDesc(&ConstantBufferDesc);
			_EntryName;

			ResDesc.Name;
			UEngineStructuredBufferSetter& NewSetter = StructureBuffers[_Type][UpperName];
			NewSetter.SetName(ResDesc.Name);
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;

			std::shared_ptr<UEngineStructuredBuffer> Buffer = UEngineStructuredBuffer::CreateAndFind(_Type, ResDesc.Name, NewSetter.BufferSize);
			NewSetter.Res = Buffer;
			break;
		}
		default:
			MsgBoxAssert("처리할 수 없는 타입입니다.")
			break;
		}
	}
}

void UEngineConstantBufferSetter::Setting()
{
	// 상수 버퍼 세팅

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + "상수버퍼에 세팅을 해주지 않았습니다. ");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}

void UEngineStructuredBufferSetter::PushData(const void* _Data, UINT _Size)
{

}
