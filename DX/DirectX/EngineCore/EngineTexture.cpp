#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

#pragma comment (lib, "DirectXTex.lib")

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

void UEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc)
{
	Desc = _Desc;
	
	GEngine->GetDirectXDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateRenderTargetView();
	}
	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
	{

	}
	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{

	}
}

void UEngineTexture::ResCreate(ID3D11Texture2D* _Texture)
{


}

void UEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타켓뷰를 생성하려고 했습니다.");
		return;
	}

	// 텍스처 메모리에서 이미지를 수정할 수 있는 권한을 만든다.
	// 다이렉트에서 뭔가를 하려면 근본적으로 2가지 관련
	// 메모리 -> DEvice;
	// 렌더링 -> COntext;

	HRESULT Reslut = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Reslut)
	{
		MsgBoxAssert("랜더타켓 뷰 생성에 실패");
		return;
	}


}

void UEngineTexture::CreateShaderResourceView()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 쉐이더 리소스 뷰를 생성하려고 했습니다.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패");
		return;
	}
}
