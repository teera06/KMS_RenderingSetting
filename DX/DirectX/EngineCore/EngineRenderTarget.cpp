#include "PreCompile.h"
#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineCore.h"
#include "RenderUnit.h"

URenderUnit UEngineRenderTarget::CopyUnit;

UEngineRenderTarget::UEngineRenderTarget()
{
}

UEngineRenderTarget::~UEngineRenderTarget()
{
}

void UEngineRenderTarget::CreateDepthTexture(int _Index)
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };
	Desc.ArraySize = 1;

	Desc.Width = Textures[_Index]->GetScale().uiX();
	Desc.Height = Textures[_Index]->GetScale().uiY();

	// z값 하나만 사용하는것.
	// 뒤의 1바이트를 심플한 스탠실 값이라는것으로 사용한다.
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;

	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	DepthTexture = UEngineTexture::Create(Desc);
}

void UEngineRenderTarget::Clear()
{
	// 어떠한 그림의 클리어
	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}

	if(nullptr!=DepthTexture)
	{
		// 1.0f 클리어 할때 무슨 값이냐?
		GEngine->GetDirectXContext()->ClearDepthStencilView(DepthTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void UEngineRenderTarget::Setting(bool IsDepth)
{
	ID3D11DepthStencilView* DSV = nullptr;

	if (true == IsDepth && nullptr != DepthTexture)
	{
		DSV = DepthTexture->GetDSV();
	}

	// 깊이버퍼는 나중에
	GEngine->GetDirectXContext()->OMSetRenderTargets(static_cast<UINT>(RTVs.size()), &RTVs[0], DSV);
}

void UEngineRenderTarget::Copy(std::shared_ptr<UEngineRenderTarget> _Other)
{
	Clear();
	Merge(_Other);
}

void UEngineRenderTarget::Merge(std::shared_ptr<UEngineRenderTarget> _Other, int _Index)
{
	// 내가 대상이니까 
	Setting();

	std::shared_ptr<UEngineTexture> CopyTarget = _Other->Textures[_Index];
	// 엄청중요한 

	UEngineRenderTarget::CopyUnit.Resources->SettingTexture("Image", CopyTarget, "POINT");
	UEngineRenderTarget::CopyUnit.Render(0.0f);
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVs.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}

void UEngineRenderTarget::RenderTargetInit()
{
	UEngineRenderTarget::CopyUnit.SetMesh("FullRect");
	UEngineRenderTarget::CopyUnit.SetMaterial("TargetCopy");
}
