#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct IDXGIApter;

class UEngineRenderTarget;

class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	ID3D11Device* GetDevice()
	{
		return Device;
	}

	ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	void RenderStart();
	
	void RenderEnd();

private:

	// �޸�(�׸�, �̹���, �� , ����) ����
	ID3D11Device* Device = nullptr;
	// �׸� �� ���
	ID3D11DeviceContext* Context = nullptr;

	// ���� ���۸�
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIApter* Adapter = nullptr;

	std::shared_ptr<UEngineRenderTarget> BackBufferRenderTarget = nullptr;
};

