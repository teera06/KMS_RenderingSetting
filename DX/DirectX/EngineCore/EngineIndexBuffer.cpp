#include "PreCompile.h"
#include "EngineIndexBuffer.h"
#include "EngineCore.h"

UEngineIndexBuffer::UEngineIndexBuffer()
{
}

UEngineIndexBuffer::~UEngineIndexBuffer()
{
}

void UEngineIndexBuffer::Setting()
{
#ifdef DEBUG
	if (nullptr == Buffer)
	{
		MsgBoxAssert("�ε��� ���۰� ������ �ʾҴµ� ������ �Ǿ����ϴ�.");
	}
#endif // DEBUG
	GEngine->GetDirectXContext()->IASetIndexBuffer(Buffer, Format, Offset);

}
