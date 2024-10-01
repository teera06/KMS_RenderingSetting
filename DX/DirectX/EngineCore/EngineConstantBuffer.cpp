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
		MsgBoxAssert(GetName() + "상수버퍼에 nullptr인 데이터를 세팅하려고 했습니다.");
	}

	if (0 >= _Size)
	{
		MsgBoxAssert(GetName() + "상수버퍼에 0이하의 데이터를 세팅하려고 했습니다.");
	}
#endif // DEBUG

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// 버퍼를 잠시 변경하기 위해서 열겠다.
	// Map 최대한 적게 사용하는게 좋다.
	GEngine->GetDirectXContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

#ifdef DEBUG
	if (nullptr == Data.pData)
	{
		MsgBoxAssert(GetName() + "그래픽 카드가 수정을 거부");
	}
#endif // DEBUG
	// Data.pData 그래픽카드에 넣어주는 주소
	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// 다썼어 다시 잠금
	GEngine->GetDirectXContext()->Unmap(Buffer, 0);
}

void UEngineConstantBuffer::ResCreate(UINT _ByteSize)
{
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// CPU에서 상수버퍼의 내용을 덮어 씌우겠습니다.

	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("상수 버퍼 생성에 실패");
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
		MsgBoxAssert("처리가 완료되지 않은 상수버퍼 쉐이더 세팅 타입입니다.");
		break;
	}
}
