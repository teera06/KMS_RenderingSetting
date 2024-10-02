#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct IDXGIApter;
struct IDXGIAdapter;

class UEngineRenderTarget;
class UEngineWindow;

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

	// nullptr의 가능성을 없애버리기 위해서 
	void Initialize(const UEngineWindow& _Window, const float4& _Clearclolor);

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

	// 메모리(그림, 이미지, 점 , 등등등) 관리
	ID3D11Device* Device = nullptr;
	// 그릴 때 사용
	ID3D11DeviceContext* Context = nullptr;

	const UEngineWindow* windowPtr = nullptr;

	// 더블 버퍼링
	IDXGISwapChain* SwapChain = nullptr;

	IDXGIAdapter* Adapter = nullptr;

	std::shared_ptr<UEngineRenderTarget> BackBufferRenderTarget = nullptr;

	IDXGIAdapter* GetHighperFormanceAdapter();
	void CreateSwapChain(const float4& _ClearColor);

	void EngineResourcesInit();
};

