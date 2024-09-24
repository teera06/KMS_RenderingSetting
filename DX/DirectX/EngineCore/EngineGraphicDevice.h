#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct IDXGIApter;

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

private:

	// �޸�(�׸�, �̹���, �� , ����) ����
	ID3D11Device* Device = nullptr;
	// �׸� �� ���
	ID3D11DeviceContext* Context = nullptr;

	// ���� ���۸�
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIApter* Adapter = nullptr;


};

