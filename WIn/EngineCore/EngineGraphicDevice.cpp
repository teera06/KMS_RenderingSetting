#include <d3d11_4.h> // 다이렉트x 메인헤더 버전4 이전 버전과의 차이는 선생님도 관심 없음
#include <d3dcompiler.h> // 쉐이더 컴파일러 인터페이스. 쉐이더가 뭔지는 추후 배움
#include "EngineGraphicDevice.h"
#include "EngineRenderTarget.h"
#include "EngineDebug.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
}

// 뭔가를 그리기 전에 한번 깨끗하게 화면을 지움
void UEngineGraphicDevice::RenderStart()
{
	BackBufferRenderTarget->Clear();
}

// 그려진걸 한번 윈도우에 출력
void UEngineGraphicDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("해상도나 디바이스 관련 설정이 변경 되었습니다");
		return;
	}
}
