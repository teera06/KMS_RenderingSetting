#include "PreCompile.h"
#include "EngineInputLayOut.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"

UEngineInputLayOut::UEngineInputLayOut()
{
}

UEngineInputLayOut::~UEngineInputLayOut()
{
}

void UEngineInputLayOut::ResCreate(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader)
{
	if (nullptr == _Buffer)
	{
		MsgBoxAssert("��ǲ���̾ƿ��� ���鶧 ���۰� nullptr");
	}

	UVertexLayOutInfo

	//if()
}

void UEngineInputLayOut::Setting()
{
}
