#pragma once

#include "ThirdParty\DirectxTex\inc\\DirectXTex.h"

class UEngineTexture
{
public:
	
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

private:

	// �̹��� �� ��ü
	// DirectX������ �޸𸮸� �ǹ��ϴ� �ڵ�
	// �޸� ���� ����

	ID3D11Texture2D* Texture2D = nullptr;

	// DirectX������ �̹���(�޸�) ���� ���� (���⿡ �׸� �� �ִ� ����)
	ID3D10RenderTargetView* RTV = nullptr;

	// directx���� �̹����� ���̴��� ������ �� �ִ� ����
	ID3D11ShaderResourceView* SRV = nullptr;

	ID3D11DepthStencilView* DSV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	
};

