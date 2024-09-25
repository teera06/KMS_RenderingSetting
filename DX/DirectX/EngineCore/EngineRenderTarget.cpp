#include "PreCompile.h"
#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineCore.h"

UEngineRenderTarget::UEngineRenderTarget()
{
}

UEngineRenderTarget::~UEngineRenderTarget()
{
}

void UEngineRenderTarget::Clear()
{
	// ��� �׸��� Ŭ����
	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}

	if(nullptr!=DepthTexture)
	{
		// 1.0f Ŭ���� �Ҷ� ���� ���̳�?
		GEngine->GetDirectXContext()->ClearDepthStencilView(DepthTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVs.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}
