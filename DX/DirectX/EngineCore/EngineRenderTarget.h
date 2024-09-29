#pragma once

#include <EnginePlatform/EngineResources.h>
// 랜더 타켓 -> 그 이미지를 편집하고 그리고 복사하는 기능을 가진 애
// 효과를 준다 -> 그린다.
class UEngineTexture;
class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>, public std::enable_shared_from_this<UEngineRenderTarget>
{

public:
	// constrcuter destructer
	UEngineRenderTarget();
	~UEngineRenderTarget();

	// delete Function
	UEngineRenderTarget(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget(UEngineRenderTarget&& _Other) noexcept = delete;
	UEngineRenderTarget& operator=(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget& operator=(UEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineRenderTarget> Create(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
	{
		std::shared_ptr<UEngineRenderTarget> NewRes = CreateResUnName();
		NewRes->AddNewTexture(_Texture, _Color);
		return NewRes;
	}

	static std::shared_ptr<UEngineRenderTarget> Create()
	{
		std::shared_ptr<UEngineRenderTarget> NewRes = CreateResUnName();
		return NewRes;
	}


	void Clear();

private:
	// 텍스처 여러개를 엮어서 사용할 수 있게 한다.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;
	std::shared_ptr<UEngineTexture> DepthTexture = nullptr;

	std::vector<ID3D11RenderTargetView*> RTVs;
	std::vector<float4> ClearColors;

	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color);

	

	


};

