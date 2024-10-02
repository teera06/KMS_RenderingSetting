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
		MsgBoxAssert("레스터라이저 생성에 실패");
		return;
	}
#endif // DEBUG

}

void UEngineRasterizer::Setting()
{
#ifdef DEBUG
	if (nullptr == State) 
	{
		MsgBoxAssert("만들어지지 않은 레스터라이저를 세팅");
	}
#endif // DEBUG

	GEngine->GetDirectXContext()->RSSetState(State);

}
