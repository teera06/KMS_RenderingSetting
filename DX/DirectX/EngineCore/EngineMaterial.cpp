#include "PreCompile.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"
#include "EngineRasterizer.h"

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
#ifdef DEBUG
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
#ifdef DEBUG
	if (nullptr == Rasterizer)
	{
		MsgBoxAssert("�����Ͷ������� �������� �ʰ� ������ �Ϸ��� �߽��ϴ�.");
		return;
	}
#endif // DEBUG

	Rasterizer->Setting();
}
