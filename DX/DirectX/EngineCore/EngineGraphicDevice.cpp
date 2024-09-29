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
		MsgBoxAssert("Open ���� ���� ������� �׷��� ī�� ��ġ�� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	// �� �׷��� ī�尡 ���̷�Ʈ X�� ����� ���� ������ �� �ִ��� �˾Ƴ��� ���� ����
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �׷���ī���� ���� ����� ���� �׷���ī�带 �������� �Լ�
	Adapter = GetHighperFormanceAdapter();

	if (nullptr == Adapter)
	{
		MsgBoxAssert("�׷���ī�尡 �������� �ʴ� ��ǻ�� �Դϴ�.");
		return;
	}


	// �׷��� ī�带 ã������
	// Adapter �׷��� ī�忡 ����� ���� �� �ִ� ����̽��� ���ؽ�Ʈ�� �����.
	
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
		MsgBoxAssert("�׷���ī�尡 ������ ���� ���� ���ؽ�Ʈ �����ϴµ� ����");
		return;
	}

	if (nullptr == Device)
	{
		MsgBoxAssert("�׷���ī�尡 �޸����� ���� ����̽��� �����ϴµ� ����");
		return;
	}

	if (S_OK != Result)
	{
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("���̷�Ʈ 11������ ����� �� ���� �׷��� ī�� �Դϴ�.");
		return;
	}

	// CPU���� ���� ��Ƽ������� �����ϰ� ����
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		if (RPC_E_CHANGED_MODE != Result)
		{
			MsgBoxAssert("��Ƽ������ �ɼ��� ����� ���� �����ϴ�.");
			return;
		}
	}

	windowPtr = &_Window;

	CreateSwapChain(_Clearclolor);

	
}

void UEngineGraphicDevice::RenderStart()
{
	// ������ �׸��� ���� �ѹ� ȭ�� ����
	BackBufferRenderTarget->Clear();
}

void UEngineGraphicDevice::RenderEnd()
{
	// BackBufferRenderTarget�� �׷����� ȭ�鿡 �׷���
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("�ػ󵵳� ����̽� ���� ������ ���� �Ǿ����ϴ�");
		return;
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighperFormanceAdapter()
{
	// �׷��� ī�尡 2�� ���
	// ���̷�Ʈ X ���̺귯���� ����� �뵵
	IDXGIFactory* Factory = nullptr;
	// Adapter�� ����� ������ Factory �ʿ��ϴ�.
	IDXGIAdapter* Adapter = nullptr;

	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	size_t VideoMemory = 0;
	// �׷��� ī�� ���� ū�ְ� ���� ������ ���� �׷��� ī���� ����


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
	// ����ü�� ��ü�� ���
	// ���� ���������� ������ �̹��� ó��
	// �׸��� �׷����� ���� �������� �� �����Ǿ��ִ� ������ ������ �����������̶�� �Ѵ�.
	// ����ü���� �� ������ ������������ ���� ������ �ܰ� ���
	// ����Ϳ� ���
	// ���������� ������ �ִ� �׸��� ������ ����� �ٽ� �׸��� �� ��� �������� ���� �������� ���
	

	// �ػ�
	float4 Resolution = windowPtr->GetWindowScale();

	// ����ü���� ����� ���� ����ü ����� ����
	DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = Resolution.iX();
	ScInfo.BufferDesc.Height = Resolution.iY();
	ScInfo.OutputWindow = windowPtr->GetHWND();

	// �ֻ��� ����Ϳ� �󸶳� ������ �����Ұų�
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	// ���� ����
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ����� �ȼ��� �����ϴ� ���� ����� �״��

	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ����ü�� �뵵
	// 
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;


	// ���ø�
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	// DXGI_SWAP_EFFECT_FLIP_DISCARD 2���� ����� �������.
	// �̰Ŷ����� ȭ���� ������
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ScInfo.Windowed = true;

	// ����ü���� ����ԵǸ�
	// DC�� ����� ���ο� ȭ�� ũ�⸸�� �ؽ�ó�� ����� �ش�.

	IDXGIFactory* pF = nullptr;

	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	Adapter->Release();
	pF->Release();

	// ���� ������ ȭ��ũ�⸸�� directx�� image�� ��� �ִ�.
	// 

	ID3D11Texture2D* DXBackBufferTexture = nullptr;

	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)))
	{
		MsgBoxAssert("����� �ؽ�ó�� ������ ���߽��ϴ�.");
		return;
	}

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Create(DXBackBufferTexture);

	// �׸� �� �ִ� �����̳� ����� ��� -> ����Ÿ���̶�� �ɷ� ����
	BackBufferRenderTarget = UEngineRenderTarget::Create(Texture, _ClearColor);
}
