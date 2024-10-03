#include "PreCompile.h"
#include "RenderUnit.h"

#include "EngineMesh.h"
#include "EngineMaterial.h"

#include "EngineInputLayOut.h"

#include "EngineCore.h"
#include "EngineShaderResources.h"
#include "EngineShader.h"

URenderUnit::URenderUnit()
{
}

URenderUnit::~URenderUnit()
{
}

void URenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 메시를 세팅하려고 햇습니다.");
		return;
	}

	if (nullptr != Material)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	float4 ScreenScale = GEngine->EngineWindow.GetWindowScale();

	BaseValue.ScreenX = ScreenScale.X;
	BaseValue.ScreenY = ScreenScale.Y;


	Material = UEngineMaterial::FindRes(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼를 세팅하려고 했습니다." + std::string(_Name));
		return;
	}

	if (nullptr != Mesh)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}

	Resources->Reset();
	ResCopy(Material->GetVertexShader().get());
	ResCopy(Material->GetPixelShader().get());


	if (true == Resources->IsConstantBuffer("FBaseRenderValue"))
	{
		Resources->SettingConstantBuffer("FBaseRenderValue", BaseValue);
	}

	MaterialSettingEnd();


}

void URenderUnit::RenderingSetting()
{
	// 버텍스 버퍼 세팅
	Mesh->InputAssmbler1Setting();
	// 인풋 레이아웃
	LayOut->Setting();

	// 버텍스 쉐이더 
	Material->VertexShaderSetting();

	// 인덱스 버퍼 세팅
	Mesh->InputAssmbler2Setting();

	// 레스터라이저 세팅
	Material->RasterizerSetting();

	// 픽셀 쉐이더 세팅
	Material->PixelShaderSetting();

	// OutPut Merger -> DepthStencil 세팅
	Material->DepthStencilSetting();

	// OutPUt Merger -> 블랜드 세팅
	Material->BlendSetting();
}

void URenderUnit::ResCopy(UEngineShader* _Shader)
{
	// 상수버퍼 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers
			= Resources->ConstantBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers
			= ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> Setter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	// 텍스처 세팅 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& RendererTexture
			= Resources->Textures;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& ShaderTextures
			= ShaderResources->Textures;

		for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>> Setters : ShaderTextures)
		{
			for (std::pair<const std::string, UEngineTextureSetter> Setter : Setters.second)
			{
				RendererTexture[Setters.first][Setter.first] = Setter.second;
			}
		}
	}


	// 샘플러 세팅 복사
	{
		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& RendererSampler
			= Resources->Samplers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& ShaderSamplers
			= ShaderResources->Samplers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>> Setters : ShaderSamplers)
		{
			for (std::pair<const std::string, UEngineSamplerSetter> Setter : Setters.second)
			{
				RendererSampler[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	{
		std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& RendererSetters
			= Resources->StructuredBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>>& ShaderSetters
			= ShaderResources->StructuredBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineStructuredBufferSetter>> Setters : ShaderSetters)
		{
			for (std::pair<const std::string, UEngineStructuredBufferSetter> Setter : Setters.second)
			{
				RendererSetters[Setters.first][Setter.first] = Setter.second;
			}
		}
	}
}

bool URenderUnit::Render(float _DeltaTime)
{
	if (nullptr == Mesh)
	{
		MsgBoxLog("매쉬가 세팅되지 않았습니다.")
			return false;
	}

	if (nullptr == Material)
	{
		MsgBoxLog("머티리얼이 세팅되지 않았습니다.")
			return false;
	}

	RenderingSetting();

	Resources->SettingAllShaderResources();
}

void URenderUnit::Update(float _DeltaTime)
{
	BaseValue.AccTime += _DeltaTime;
}
