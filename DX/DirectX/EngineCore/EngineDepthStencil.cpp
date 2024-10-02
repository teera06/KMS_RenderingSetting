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
		MsgBoxAssert("레스터라이저 생성에 실패");
		return;
	}
#endif // DEBUG


}

void UEngineDepthStencil::Setting()
{
#ifdef DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("만들어지지 않는 DepthStencil 세팅하려고 했습니다." + GetName());
	}
#endif // DEBUG

	GEngine->GetDirectXContext()->OMSetDepthStencilState(State, 0);
}
