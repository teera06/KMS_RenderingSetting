#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineRenderTarget.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
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
	

	//float4 Resolution = 
}
