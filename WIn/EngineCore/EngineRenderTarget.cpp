#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineCore.h"
//#include <d3d11.h>

UEngineRenderTarget::UEngineRenderTarget()
{
}

UEngineRenderTarget::~UEngineRenderTarget()
{
}

void UEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RTVS.size(); i++)
	{
		int index = static_cast<int>(i);
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVS[index], ClearColors[index].Arr1D);
	}

	if (nullptr != DepthTexture)
	{
		GEngine->GetDirectXContext()->ClearDepthStencilView(DepthTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVS.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}
