#include "PreCompile.h"
#include "EngineSampler.h"
#include "EngineCore.h"

UEngineSampler::UEngineSampler()
{
}

UEngineSampler::~UEngineSampler()
{
}

void UEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateSamplerState(&_Info, &State);
#ifdef _DEBUG
	if(S_OK!=Result)
	{
		MsgBoxAssert("샘플러 생성에 실패");
		return;
	}
#endif // _DEBUG


}

void UEngineSampler::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::NONE:
		break;
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetSamplers(_Slot, 1, &State);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetSamplers(_Slot, 1, &State);
		break;
	default:
		MsgBoxAssert("타입이 불분명한 샘플러 세팅입니다.");
		break;
	}
}

void UEngineSampler::Reset(EShaderType _Type, UINT _Slot)
{
	ID3D11SamplerState* NullptrState = nullptr;

	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetSamplers(_Slot, 1, &NullptrState);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetSamplers(_Slot, 1, &NullptrState);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("타입이 불분명한 셈플러 세팅입니다.");
		break;
	}
}
