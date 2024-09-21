#pragma once
#include <EnginePlatform/EngineResources.h>
#include "ThirdParty\DirectXTex\inc\DirectXTex.h"
// 실제적인 랜더링 대상지정기능과 클리어등등 랜더링에 관련된 기능
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
	// 이미지 그 자체
	// Directx에서 메모리를 의미하는 핸들
	// 그리고 그런 메모리가 있어야 메모리 수정 권한

	ID3D11Texture2D* Texture2D = nullptr;

	// DIrectx에서는 이미지(메모리) 수정 권한(여기에 그릴 수 있는 권한)
	ID3D11RenderTargetView* RTV = nullptr;

	//Directx에서 이미지를 쉐이더에 세팅할 수 있는 권한
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11DepthStencilView* DSV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

};

