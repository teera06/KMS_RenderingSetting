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
	// ���̷�Ʈ���� � �޸𸮸� �Ҵ��� �� �ʱⰪ�� �־��ְ� ������ �̰� �־��ش�.
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

	// ũ��
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);

	// �뵵
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// CPU�� ���ٰ����Ѱ�
	BufferInfo.CPUAccessFlags = 0;

	// �׷��� ī�忡 ����
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("�ε��� ���� ������ ����");
		return;
	}
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
