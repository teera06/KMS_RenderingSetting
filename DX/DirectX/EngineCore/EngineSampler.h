#pragma once

class UEngineSampler : public UEngineResources<UEngineSampler>
{
public:
	// constrcuter destructer
	UEngineSampler();
	~UEngineSampler();

	// delete Function
	UEngineSampler(const UEngineSampler& _Other) = delete;
	UEngineSampler(UEngineSampler&& _Other) noexcept = delete;
	UEngineSampler& operator=(const UEngineSampler& _Other) = delete;
	UEngineSampler& operator=(UEngineSampler&& _Other) noexcept = delete;

private:
	ID3D11SamplerState* State = nullptr;
};

