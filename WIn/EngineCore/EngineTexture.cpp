#include <d3d11_4.h> // ���̷�Ʈx ������� ����4 ���� �������� ���̴� �����Ե� ���� ����
#include <d3dcompiler.h> // ���̴� �����Ϸ� �������̽�. ���̴��� ������ ���� ���
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
	// ���ҽ�, ����Ÿ��, ���̴�, ���� �⺻ ����
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
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�Ϻ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �ؽ�ó �޸𸮿��� ������ �� �ִ� ���� 
	// ���̷�Ʈ���� ������ �Ϸ��� �ٺ������� 2���� ���õǾ� �ִ�.
	// �޸� -> Device
	// ������ -> Context

	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�� �� ������ ����");
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
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�Ϻ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("���̴� ���ҽ� �� ������ ����");
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
		MsgBoxAssert("��������� ���� ����ó�� ����Ÿ�Ϻ並 �����ҷ��� �߽��ϴ�.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if (S_OK != Result)
	{
		MsgBoxAssert("DepthStencilView �� ������ ����");
		return;
	}

}
