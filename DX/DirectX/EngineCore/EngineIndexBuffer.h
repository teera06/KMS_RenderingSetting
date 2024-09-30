#pragma once
#include "EngineBuffer.h"

class UEngineMesh;
class UEngineIndexBuffer : public UEngineResources<UEngineIndexBuffer>, public UEngineBuffer 
{
	friend UEngineMesh;
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
	UINT Count = 0;
	UINT Offset = 0;

	void Setting();
	

};

