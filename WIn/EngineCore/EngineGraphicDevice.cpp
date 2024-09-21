#include <d3d11_4.h> // ���̷�Ʈx ������� ����4 ���� �������� ���̴� �����Ե� ���� ����
#include <d3dcompiler.h> // ���̴� �����Ϸ� �������̽�. ���̴��� ������ ���� ���
#include "EngineGraphicDevice.h"
#include "EngineRenderTarget.h"
#include "EngineDebug.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

// ������ �׸��� ���� �ѹ� �����ϰ� ȭ���� ����
void UEngineGraphicDevice::RenderStart()
{
	BackBufferRenderTarget->Clear();
}

// �׷����� �ѹ� �����쿡 ���
void UEngineGraphicDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("�ػ󵵳� ����̽� ���� ������ ���� �Ǿ����ϴ�");
		return;
	}
}
