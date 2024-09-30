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
		MsgBoxAssert("인덱스 버퍼가 만들지 않았는데 세팅이 되었습니다.");
	}
#endif // DEBUG
	GEngine->GetDirectXContext()->IASetIndexBuffer(Buffer, Format, Offset);

}
