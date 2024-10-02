#pragma once
#include "EngineShader.h"

class UEngineMaterial;

class UEnginePixelShader : public UEngineResources<UEnginePixelShader>, public UEngineShader
{
	friend UEngineMaterial;
public:
	// constrcuter destructer
	UEnginePixelShader();
	~UEnginePixelShader();

	// delete Function
	UEnginePixelShader(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader(UEnginePixelShader&& _Other) noexcept = delete;
	UEnginePixelShader& operator=(const UEnginePixelShader& _Other) = delete;
	UEnginePixelShader& operator=(UEnginePixelShader&& _Other) noexcept = delete;

private:
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT _Low);

	void Setting();
};

