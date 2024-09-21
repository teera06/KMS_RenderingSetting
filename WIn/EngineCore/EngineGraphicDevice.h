#pragma once



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

	// ������ �׸��� ���� �ѹ� �����ϰ� ȭ�� ����
	void RenderStart();




private:

	// Device->LoadTexture() -> �޸� (�׸�, �̹���, �� ���) ����
	struct ID3D11Device* Device = nullptr;

	// Context -> MeshRender -> �׸� ��
	struct ID3D11DeviceContext* context = nullptr;

	// ���� ���۸�, ����ü��
	struct IDXGISwapChain* SwapChain = nullptr;

};
