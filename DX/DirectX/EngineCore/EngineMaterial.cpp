#include "PreCompile.h"
#include "EngineMaterial.h"
#include "EngineVertexShader.h"

UEngineMaterial::UEngineMaterial()
{
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
