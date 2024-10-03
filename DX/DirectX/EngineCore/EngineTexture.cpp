#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

#pragma comment (lib, "DirectXTex.lib")

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
	if (nullptr != SRV)
	{
		SRV->Release();
	}

	if (nullptr != RTV)
	{
		RTV->Release();
	}

	if (nullptr != DSV)
	{
		DSV->Release();
	}

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
		CreateShaderResourceView();
	}
	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
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

void UEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DSV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� DSV�� �����Ϸ��� �ߴ�.");
		return;
	}

	HRESULT Result = GEngine->GetDirectXDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if(S_OK != Result)
	{ 
		MsgBoxAssert("DSV ������ ����");
		return;
	}
}

void UEngineTexture::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::NONE:
		break;
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSGetShaderResources(_Slot, 1, &SRV);
		break;
	default:
		MsgBoxAssert("Ÿ���� �Һи��� �ؽ�ó ����");
		break;
	}
}

void UEngineTexture::Reset(EShaderType _Type, UINT _Slot)
{
	ID3D11ShaderResourceView* NullptrSRV = nullptr;

	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("Ÿ���� �Һи��� �ؽ�ó �����Դϴ�.");
		break;
	}
}
