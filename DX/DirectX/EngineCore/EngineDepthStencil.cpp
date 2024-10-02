#include "PreCompile.h"
#include "EngineDepthStencil.h"
#include "EngineCore.h"

UEngineDepthStencil::UEngineDepthStencil()
{

}

UEngineDepthStencil::~UEngineDepthStencil()
{
	if (nullptr != State)
	{
		State->Release();
	}
}

void UEngineDepthStencil::ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateDepthStencilState(&_Info, &State);
#ifdef DEBUG
	if (S_OK != Result)
	{
		MsgBoxAssert("�����Ͷ����� ������ ����");
		return;
	}
#endif // DEBUG


}

void UEngineDepthStencil::Setting()
{
#ifdef DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("��������� �ʴ� DepthStencil �����Ϸ��� �߽��ϴ�." + GetName());
	}
#endif // DEBUG

	GEngine->GetDirectXContext()->OMSetDepthStencilState(State, 0);
}
