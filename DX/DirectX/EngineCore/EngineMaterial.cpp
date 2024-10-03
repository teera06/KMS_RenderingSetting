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
		MsgBoxAssert("�������� ���� ���ؽ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == VertexShader)
	{
		MsgBoxAssert("���ؽ� ���̴��� �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
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
		MsgBoxAssert("�������� ���� �����Ͷ������� ����");
		return;
	}
}

void UEngineMaterial::RasterizerSetting()
{
#ifdef _DEBUG
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("�����Ͷ������� �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� �ȼ� ���̴��� �����Ϸ��� �߽��ϴ�.");
		return;
	}


}

void UEngineMaterial::PixelShaderSetting()
{
#ifdef _DEBUG
	if (nullptr == PixelShader) 
	{
		MsgBoxAssert("�ȼ� ���̴��� �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ���� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void UEngineMaterial::BlendSetting()
{
#ifdef _DEBUG
	if(nullptr==Blend)
	{
		MsgBoxAssert("���� �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
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
		MsgBoxAssert("�������� �ʴ� ������ �����Ϸ��� �޽��ϴ�.");
		return;
	}
}

void UEngineMaterial::DepthStencilSetting()
{
#ifdef _DEBUG
	if (nullptr == DepthStencil)
	{
		MsgBoxAssert("���� ������ �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
		return;
	}
#endif // DEBUG

	DepthStencil->Setting();
}

