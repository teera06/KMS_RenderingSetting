#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineRenderTarget.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

void UEngineGraphicDevice::RenderStart()
{
	// 뭔가를 그리기 전에 한번 화면 지움
	BackBufferRenderTarget->Clear();
}

void UEngineGraphicDevice::RenderEnd()
{
	// BackBufferRenderTarget에 그련진걸 화면에 그려라
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("해상도나 디바이스 관련 설정이 변경 되었습니다");
		return;
	}
}
