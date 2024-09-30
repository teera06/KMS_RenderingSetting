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
		MsgBoxAssert("존재하지 않은 버텍스 쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void UEngineMaterial::VertexShaderSetting()
{
#ifdef DEBUG
	if (nullptr == VertexShader)
	{
		MsgBoxAssert("버텍스 쉐이더를 세팅하지 않고 랜더링 하려고 했습니다.");
		return;
	}
#endif // DEBUG
	
	VertexShader->Setting();
}
