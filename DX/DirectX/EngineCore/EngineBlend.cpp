#include "PreCompile.h"
#include "EngineBlend.h"
#include "EngineCore.h"

UEngineBlend::UEngineBlend()
{
}

UEngineBlend::~UEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
	}
}

void UEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateBlendState(&_Info, &State);

#ifdef _DEBUG
	if (S_OK != Result)
	{
		MsgBoxAssert("블랜드 생성에 실패");
		return;
	}
#endif // DEBUG

}

void UEngineBlend::Setting()
{
#ifdef _DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("만들어지지 않은 블랜드 세팅하려고 했습니다.");
	}
#endif // _DEBUG

	GEngine->GetDirectXContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}
