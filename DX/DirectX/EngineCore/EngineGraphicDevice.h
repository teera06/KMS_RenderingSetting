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

	// 메모리(그림, 이미지, 점 , 등등등) 관리
	ID3D11Device* Device = nullptr;
	// 그릴 때 사용
	ID3D11DeviceContext* Context = nullptr;

	// 더블 버퍼링
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIApter* Adapter = nullptr;


};

