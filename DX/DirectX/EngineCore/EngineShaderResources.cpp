#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

#include "EngineTexture.h"
#include "EngineSampler.h"

void EngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
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

bool EngineShaderResources::IsConstantBuffer(std::string_view _Name)
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

void EngineShaderResources::SettingTexture(std::string_view _TexName, std::string_view _ImageName, std::string_view _SamperName)
{
	std::shared_ptr<UEngineTexture> FindTexture = UEngineTexture::FindRes(_ImageName);
	SettingTexture(_TexName, FindTexture, _SamperName);
}

void EngineShaderResources::SettingTexture(std::string_view _TexName, std::shared_ptr<UEngineTexture> _Texture, std::string_view _SamperName)
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
