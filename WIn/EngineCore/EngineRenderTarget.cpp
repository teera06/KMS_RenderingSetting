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

void UEngineRenderTarget::CreateTexTure(DXGI_FORMAT _Format, float4 _Scale, float4 _ClearColor)
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };

	Desc.ArraySize = 1;
	Desc.Width = _Scale.iX();
	Desc.Height = _Scale.iY();
	Desc.Format = _Format;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.MipLevels = 1;

	// 그래픽카드에서 관리
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::Create(Desc);

	AddNewTexture(Tex, _ClearColor);
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

void UEngineRenderTarget::Setting(bool _IsDepth)
{
	ID3D11DepthStencilView* DSV = nullptr;

	if (true == _IsDepth && nullptr != DepthTexture)
	{
		DSV = DepthTexture->GetDSV();
	}

	// 깊이버퍼
	GEngine->GetDirectXContext()->OMSetRenderTargets(static_cast<UINT>(RTVS.size()), &RTVS[0], DSV);
}

void UEngineRenderTarget::Merge(std::shared_ptr<UEngineRenderTarget> _Other, int _index)
{
	Setting();

	// 엄청 중요
	std::shared_ptr<UEngineTexture> CopyTarget = _Other->Textures[_index];

	
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVS.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}
