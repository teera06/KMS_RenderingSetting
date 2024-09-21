#pragma once
#include "EnginePlatform/EngineResources.h"
#include "EngineBase/EngineMath.h"
//#include <d3d11.h>
// 렌더 타겟 : 그 이미지를 편집하고 복사하는 기능을 가진 애

class ULevel;
class UEngineTexture;
class UEngineGraphicDevice;

class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>, public std::enable_shared_from_this<UEngineRenderTarget>
{
	friend ULevel;
	friend UEngineGraphicDevice;

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
		
	}
private:
	// 텍스처 여러개를 엮어서 사용할 수 있게 할거다.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;

	std::vector<struct ID3D11RenderTargetView*> RTVS;


	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color);
};

