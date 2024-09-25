#pragma once

#include <EnginePlatform/EngineResources.h>

#include "ThirdParty\DirectxTex\inc\\DirectXTex.h"

class UEngineTexture : UEngineResources<UEngineTexture>
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

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		
	}

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

	// 이미지 그 자체
	// DirectX에서는 메모리를 의미하는 핸들
	// 메모리 수정 권한

	ID3D11Texture2D* Texture2D = nullptr;

	// DirectX에서는 이미지(메모리) 수정 권한 (여기에 그릴 수 있는 권한)
	ID3D11RenderTargetView* RTV = nullptr;

	// directx에서 이미지를 쉐이더에 세팅할 수 있는 권한
	ID3D11ShaderResourceView* SRV = nullptr;

	ID3D11DepthStencilView* DSV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	void ResCreate(const D3D11_TEXTURE2D_DESC& _Desc);

	void ResCreate(ID3D11Texture2D* _Texture);
	
	void CreateRenderTargetView();
	void CreateShaderResourceView();
	void CreateDepthStencilView();
};

