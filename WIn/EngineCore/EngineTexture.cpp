#include <d3d11_4.h> // 다이렉트x 메인헤더 버전4 이전 버전과의 차이는 선생님도 관심 없음
#include <d3dcompiler.h> // 쉐이더 컴파일러 인터페이스. 쉐이더가 뭔지는 추후 배움
#include "EngineTexture.h"
#include "EngineCore.h"


#include <EnginePlatform/EngineResources.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

void UEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc)
{
	// 리소스, 랜더타켓, 쉐이더, 깊이 기본 생성
	Desc = _Desc;

	GEngine->GetDirectXDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateRenderTargetView();
	}
	if (Desc.BindFlags && D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
	{
		CreateShaderResourceVIew();
	}
	if (Desc.BindFlags && D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
	{
		CreateDepthStencilView();
	}
}

void UEngineTexture::ResCreate(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;
	Texture2D->GetDesc(&Desc);
	CreateRenderTargetView();
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

	// 텍스처 메모리에서 수정할 수 있는 권한 
	// 다이렉트에서 뭔가를 하려면 근본적으로 2가지 관련되어 있다.
	// 메모리 -> Device
	// 렌더링 -> Context

	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타켓 뷰 생성에 실패");
		return;

	}
}

void UEngineTexture::CreateShaderResourceVIew()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타켓뷰를 생성하려고 했습니다.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패");
		return;
	}
}

void UEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DSV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍츠처로 랜더타켓뷰를 생성할려고 했습니다.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if (S_OK != Result)
	{
		MsgBoxAssert("DepthStencilView 뷰 생성에 실패");
		return;
	}

}
