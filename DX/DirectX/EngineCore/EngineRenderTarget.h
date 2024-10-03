#pragma once

#include <EnginePlatform/EngineResources.h>
// ���� Ÿ�� -> �� �̹����� �����ϰ� �׸��� �����ϴ� ����� ���� ��
// ȿ���� �ش� -> �׸���.
class UEngineTexture;
class UEngineGraphicDevice;
class ULevel;

class URenderUnit;
class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>, public std::enable_shared_from_this<UEngineRenderTarget>
{
	friend ULevel;

	friend UEngineGraphicDevice;

	static URenderUnit CopyUnit;
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

	std::shared_ptr<UEngineTexture> GetTexure(int _Index = 0)
	{
		return Textures[_Index];
	}

	void CreateDepthTexture(int _Index = 0);

	void Clear();

	void Setting(bool IsDepth = false);

	// _Other �� ������ ī���Ѵ�.
	void Copy(std::shared_ptr<UEngineRenderTarget> _Other);

	// _Other �� ������ ��ģ���Ѵ�.
	void Merge(std::shared_ptr<UEngineRenderTarget> _Other, int _Index = 0);
private:
	// �ؽ�ó �������� ��� ����� �� �ְ� �Ѵ�.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;
	std::shared_ptr<UEngineTexture> DepthTexture = nullptr;

	std::vector<ID3D11RenderTargetView*> RTVs;
	std::vector<float4> ClearColors;

	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color);

	static void RenderTargetInit();

	


};

