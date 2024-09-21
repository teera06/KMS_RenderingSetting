#pragma once

#include <memory>

class UEngineRenderTarget;

class UEngineGraphicDevice
{

public:
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	// 뭔가를 그리기 전에 한번 깨끗하게 화면 지움
	void RenderStart();

	void RenderEnd();

	struct ID3D11Device* GetDevice()
	{
		return Device;
	}

	struct ID3D11DeviceContext* GetContext()
	{
		return context;
	}


private:
	// Device->LoadTexture() -> 메모리 (그림, 이미지, 점 등등) 관리
	struct ID3D11Device* Device = nullptr;

	// Context -> MeshRender -> 그릴 때
	struct ID3D11DeviceContext* context = nullptr;

	// 더블 버퍼링, 스왑체인
	struct IDXGISwapChain* SwapChain = nullptr;

	
	std::shared_ptr<UEngineRenderTarget> BackBufferRenderTarget = nullptr;
};
