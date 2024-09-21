#pragma once
#include <EnginePlatform/EngineResources.h>
#include "ThirdParty\DirectXTex\inc\DirectXTex.h"
// �������� ������ ���������ɰ� Ŭ������ �������� ���õ� ���
class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}

private:
	// �̹��� �� ��ü
	// Directx���� �޸𸮸� �ǹ��ϴ� �ڵ�
	// �׸��� �׷� �޸𸮰� �־�� �޸� ���� ����

	ID3D11Texture2D* Texture2D = nullptr;

	// DIrectx������ �̹���(�޸�) ���� ����(���⿡ �׸� �� �ִ� ����)
	ID3D11RenderTargetView* RTV = nullptr;

	//Directx���� �̹����� ���̴��� ������ �� �ִ� ����
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11DepthStencilView* DSV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

};

