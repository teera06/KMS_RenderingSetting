#include "PreCompile.h"
#include "EngineVertexBuffer.h"
#include "EngineCore.h"

UEngineVertexBuffer::UEngineVertexBuffer()
{
}

UEngineVertexBuffer::~UEngineVertexBuffer()
{
}

void UEngineVertexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	// 크기
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);

	// 용도
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// CPU에 접근 가능 한가.
	BufferInfo.CPUAccessFlags = 0;

	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}


}

void UEngineVertexBuffer::Setting()
{
#ifdef _DEBUG
	if (nullptr == Buffer)
	{
		MsgBoxAssert("만들어지지 않은 버텍스 버퍼를 세팅하려고 했습니다." + GetName());
	}
#endif

	// 1개의 버텍스 버퍼만 세팅하는 설정

	GEngine->GetDirectXContext()->IASetVertexBuffers(0, 1, &Buffer, &Size, &Offset);

}
