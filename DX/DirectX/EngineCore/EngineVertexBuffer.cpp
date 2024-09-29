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

	// ũ��
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);

	// �뵵
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// CPU�� ���� ���� �Ѱ�.
	BufferInfo.CPUAccessFlags = 0;

	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}


}

void UEngineVertexBuffer::Setting()
{
#ifdef _DEBUG
	if (nullptr == Buffer)
	{
		MsgBoxAssert("��������� ���� ���ؽ� ���۸� �����Ϸ��� �߽��ϴ�." + GetName());
	}
#endif

	// 1���� ���ؽ� ���۸� �����ϴ� ����

	GEngine->GetDirectXContext()->IASetVertexBuffers(0, 1, &Buffer, &Size, &Offset);

}
