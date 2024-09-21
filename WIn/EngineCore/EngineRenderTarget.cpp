#include "EngineRenderTarget.h"
#include <d3d11.h>

UEngineRenderTarget::UEngineRenderTarget()
{
}

UEngineRenderTarget::~UEngineRenderTarget()
{
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	//RTVS.push_back()
}
