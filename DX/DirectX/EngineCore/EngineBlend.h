#pragma once

class UEngineBlend : public UEngineResources<UEngineBlend>
{
public:
	// constrcuter destructer
	UEngineBlend();
	~UEngineBlend();

	// delete Function
	UEngineBlend(const UEngineBlend& _Other) = delete;
	UEngineBlend(UEngineBlend&& _Other) noexcept = delete;
	UEngineBlend& operator=(const UEngineBlend& _Other) = delete;
	UEngineBlend& operator=(UEngineBlend&& _Other) noexcept = delete;

private:
	ID3D11BlendState* State = nullptr;

	// 블랜드 공식에 영향을 주지 않겠다.
	// 
	float4 Factor = float4::Zero;

	// 색상 모든 부분에 블랜드 결과가 적용
	// 블랜드로 결정난 색깔이 눈에 보이게 

	UINT Mask= 0xFFFFFFFF;


	void ResCreate(const D3D11_BLEND_DESC& _Info);
};

