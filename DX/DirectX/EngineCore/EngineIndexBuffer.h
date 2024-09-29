#pragma once
#include "EngineBuffer.h"

class UEngineIndexBuffer : public UEngineResources<UEngineIndexBuffer>, public UEngineBuffer 
{
public:
	// constrcuter destructer
	UEngineIndexBuffer();
	~UEngineIndexBuffer();

	// delete Function
	UEngineIndexBuffer(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer(UEngineIndexBuffer&& _Other) noexcept = delete;
	UEngineIndexBuffer& operator=(const UEngineIndexBuffer& _Other) = delete;
	UEngineIndexBuffer& operator=(UEngineIndexBuffer&& _Other) noexcept = delete;

private:
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;

	UINT Size = 0;
	UINT COunt = 0;
	UINT Offset = 0;

	

};

