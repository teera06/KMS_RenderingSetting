#include "PreCompile.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"
#include "EngineRasterizer.h"
#include "EnginePixelShader.h"
#include "EngineBlend.h"
#include "EngineDepthStencil.h"

UEngineMaterial::UEngineMaterial()
{
	SetRasterizer("EngineBase");

}

UEngineMaterial::~UEngineMaterial()
{
}

void UEngineMaterial::SetVertexShader(std::string_view _Name)
{
	VertexShader = UEngineVertexShader::FindRes(_Name);

	if (nullptr == VertexShader)
	{
		MsgBoxAssert("존재하지 않은 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == VertexShader)
	{
		MsgBoxAssert("버텍스 쉐이더를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif // DEBUG
	
	VertexShader->Setting();
}

void UEngineMaterial::SetRasterizer(std::string_view _Name)
{
	Rasterizer = UEngineRasterizer::FindRes(_Name);
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("존재하지 않은 레스터라이저를 세팅");
		return;
	}
}

void UEngineMaterial::RasterizerSetting()
{
#ifdef _DEBUG
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("레스터라이저를 세팅하지 않고 렌더링 하려고 했습니다.");
		return;
	}
#endif // DEBUG

	Rasterizer->Setting();
}

void UEngineMaterial::SetPixeShader(std::string_view _Name)
{
	PixelShader = UEnginePixelShader::FindRes(_Name);

	if (nullptr == PixelShader)
	{
		MsgBoxAssert("존재하지 않는 픽셀 쉐이더를 세팅하려고 했습니다.");
		return;
	}


}

void UEngineMaterial::PixelShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == PixelShader) 
	{
		MsgBoxAssert("픽셀 쉐이더를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif // DEBUG

	PixelShader->Setting();
}

void UEngineMaterial::SetBlend(std::string_view _Nmae)
{
	Blend = UEngineBlend::FindRes(_Nmae);
	if (nullptr == Blend)
	{
		MsgBoxAssert("존재하지 않는 블랜드 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::BlendSetting()
{
#ifdef _DEBUG
	if(nullptr==Blend)
	{
		MsgBoxAssert("블랜드 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif // _DEBUG

	Blend->Setting();
}


void UEngineMaterial::SetDepthStencil(std::string_view _Name)
{
	DepthStencil = UEngineDepthStencil::FindRes(_Name);

	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("존재하지 않는 뎁스를 세팅하려고 햇습니다.");
		return;
	}
}

void UEngineMaterial::DepthStencilSetting()
{
#ifdef _DEBUG
	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("깊이 세팅을 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif // DEBUG

	DepthStencil->Setting();
}

