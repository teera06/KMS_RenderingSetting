#include "PreCompile.h"
#include "EngineIndexBuffer.h"
#include "EngineCore.h"

UEngineIndexBuffer::UEngineIndexBuffer()
{
}

UEngineIndexBuffer::~UEngineIndexBuffer()
{
}

void UEngineIndexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	// 다이렉트에서 어떤 메모리를 할당할 때 초기값을 넣어주고 싶으면 이걸 넣어준다.
	D3D11_SUBRESOURCE_DATA Data;

	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	if (4 == Size)
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	}
	else if (2 == Size)
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
	}

	// 크기
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);

	// 용도
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// CPU에 접근가능한가
	BufferInfo.CPUAccessFlags = 0;

	// 그래픽 카드에 저장
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("인덱스 버퍼 생성에 실패");
		return;
	}
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
