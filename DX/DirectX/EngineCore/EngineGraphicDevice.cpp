#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineRenderTarget.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
	if (nullptr != SwapChain)
	{
		SwapChain->Release();
	}

	if (nullptr != Context)
	{
		Context->Release();
	}

	if (nullptr != Device)
	{
		Device->Release();
	}
}

void UEngineGraphicDevice::Initalize(const UEngineWindow& _Window, const float4& _Clearclolor)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("Open 되지 않은 윈도우로 그래픽 카드 장치를 초기화하려고 했습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 내 그래픽 카드가 다이렉트 X를 몇버전 까지 지원할 수 있는지 알아내기 위한 변수
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드중 가장 사양이 높은 그래픽카드를 가져오는 함수
	Adapter = GetHighperFormanceAdapter();

	if (nullptr == Adapter)
	{
		MsgBoxAssert("그래픽카드가 존재하지 않는 컴퓨터 입니다.");
		return;
	}


	// 그래픽 카드를 찾았으니
	// Adapter 그래픽 카드에 명령을 내릴 수 있는 디바이스와 컨텍스트를 만든다.
	
	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (nullptr == Context)
	{
		MsgBoxAssert("그래픽카드가 랜더링 제어 권한 컨텍스트 생성하는데 실패");
		return;
	}

	if (nullptr == Device)
	{
		MsgBoxAssert("그래픽카드가 메모리제어 권한 디바이스를 생성하는데 실패");
		return;
	}

	if (S_OK != Result)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("다이렉트 11버전을 사용할 수 없는 그래픽 카드 입니다.");
		return;
	}

	// CPU에서 쓰는 멀티쓰레드로 안전하게 동작
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		if (RPC_E_CHANGED_MODE != Result)
		{
			MsgBoxAssert("멀티쓰레드 옵션을 사용할 수가 없습니다.");
			return;
		}
	}

	windowPtr = &_Window;

	CreateSwapChain(_Clearclolor);

	
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

IDXGIAdapter* UEngineGraphicDevice::GetHighperFormanceAdapter()
{
	// 그래픽 카드가 2일 경우
	// 다이렉트 X 라이브러리를 만드는 용도
	IDXGIFactory* Factory = nullptr;
	// Adapter를 만들어 내려면 Factory 필요하다.
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	size_t VideoMemory = 0;
	// 그래픽 카드 램이 큰애가 가장 성능이 좋은 그래픽 카드라고 생각


	for (int index = 0;; index++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();

	return Adapter;
}

void UEngineGraphicDevice::CreateSwapChain(const float4& _ClearColor)
{
	// 스왑체인 자체가 기능
	// 제공 최종적으로 나오는 이미지 처리
	// 그림이 그려지기 까지 벌어지는 이 고정되어있는 과정을 랜더링 파이프라인이라고 한다.
	// 스왑체인은 그 랜더링 파이프라인의 가장 마지막 단계 담당
	// 모니터에 출력
	// 랜더링에서 기존에 있던 그림을 깨끗히 지우고 다시 그리는 건 어느 랜더링이 거의 공통적인 요소
	

	// 해상도
	float4 Resolution = windowPtr->GetWindowScale();

	// 스왑체인을 만들기 위한 구조체 만들고 설정
	DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = Resolution.iX();
	ScInfo.BufferDesc.Height = Resolution.iY();
	ScInfo.OutputWindow = windowPtr->GetHWND();

	// 주사율 모니터에 얼마나 빠르게 갱신할거냐
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	// 색깔 포멧
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 모니터 픽셀을 갱신하는 순서 모니터 그대로

	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 스왑체인 용도
	// 
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;


	// 샘플링
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	// DXGI_SWAP_EFFECT_FLIP_DISCARD 2개를 교대로 보여줘라.
	// 이거때문에 화면이 깜빡임
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ScInfo.Windowed = true;

	// 스왑체인을 만들게되면
	// DC를 만들면 내부에 화면 크기만한 텍스처를 만들어 준다.

	IDXGIFactory* pF = nullptr;

	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	Adapter->Release();
	pF->Release();

	// 내가 설정한 화면크기만한 directx용 image가 들어 있다.
	// 

	ID3D11Texture2D* DXBackBufferTexture = nullptr;

	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)))
	{
		MsgBoxAssert("백버퍼 텍스처를 얻어오지 못했습니다.");
		return;
	}

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Create(DXBackBufferTexture);

	// 그릴 수 있는 권한이나 지우는 기능 -> 랜더타켓이라는 걸로 통일
	BackBufferRenderTarget = UEngineRenderTarget::Create(Texture, _ClearColor);
}
