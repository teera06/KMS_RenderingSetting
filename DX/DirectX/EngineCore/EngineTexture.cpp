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
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�Ϻ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �ؽ�ó �޸𸮿��� �̹����� ������ �� �ִ� ������ �����.
	// ���̷�Ʈ���� ������ �Ϸ��� �ٺ������� 2���� ����
	// �޸� -> DEvice;
	// ������ -> COntext;

	HRESULT Reslut = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Reslut)
	{
		MsgBoxAssert("����Ÿ�� �� ������ ����");
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
		MsgBoxAssert("��������� ���� �ؽ�ó�� ���̴� ���ҽ� �並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("���̴� ���ҽ� �� ������ ����");
		return;
	}
}
