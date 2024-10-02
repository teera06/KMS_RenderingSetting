#include "PreCompile.h"
#include "EngineRasterizer.h"
#include "EngineCore.h"

UEngineRasterizer::UEngineRasterizer()
{
}

UEngineRasterizer::~UEngineRasterizer()
{
}

void UEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRasterizerState(&_Info, &State);

#ifdef DEBUG
	if (S_OK != Result)
	{
		MsgBoxAssert("�����Ͷ����� ������ ����");
		return;
	}
#endif // DEBUG

}

void UEngineRasterizer::Setting()
{
#ifdef DEBUG
	if (nullptr == State) 
	{
		MsgBoxAssert("��������� ���� �����Ͷ������� ����");
	}
#endif // DEBUG

	GEngine->GetDirectXContext()->RSSetState(State);

}
