#include "PreCompile.h"
#include "EngineConstantBuffer.h"

#include "EngineCore.h"


UEngineConstantBuffer::UEngineConstantBuffer()
{
}

UEngineConstantBuffer::~UEngineConstantBuffer()
{

}

void UEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
#ifdef DEBUG
	if (nullptr == _Data) 
	{
		MsgBoxAssert(GetName() + "������ۿ� nullptr�� �����͸� �����Ϸ��� �߽��ϴ�.");
	}

	if (0 >= _Size)
	{
		MsgBoxAssert(GetName() + "������ۿ� 0������ �����͸� �����Ϸ��� �߽��ϴ�.");
	}
#endif // DEBUG

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// ���۸� ��� �����ϱ� ���ؼ� ���ڴ�.
	// Map �ִ��� ���� ����ϴ°� ����.
	GEngine->GetDirectXContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

#ifdef DEBUG
	if (nullptr == Data.pData)
	{
		MsgBoxAssert(GetName() + "�׷��� ī�尡 ������ �ź�");
	}
#endif // DEBUG
	// Data.pData �׷���ī�忡 �־��ִ� �ּ�
	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// �ٽ�� �ٽ� ���
	GEngine->GetDirectXContext()->Unmap(Buffer, 0);
}

void UEngineConstantBuffer::ResCreate(UINT _ByteSize)
{
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPU���� ��������� ������ ���� ����ڽ��ϴ�.

	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("��� ���� ������ ����");
		return;
	}
}

void UEngineConstantBuffer::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::NONE:
		break;
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	default:
		MsgBoxAssert("ó���� �Ϸ���� ���� ������� ���̴� ���� Ÿ���Դϴ�.");
		break;
	}
}
