#include "ContentExCore.h"
#include "TestTitleLevel.h"
#include "TestPlayLevel.h"
#include "TestLevel.h"
#include "SoftRenderingLevel.h"
#include <EnginePlatform\EngineInput.h>
#include <EnginePlatform\EngineSound.h>
#include <EnginePlatform\WindowImage.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineRandom.h>

UContentExCore::UContentExCore() 
{
	float Test = UEngineRandom::MainRandom.RandomFloat(-10.0f, 10.0f);

}

UContentExCore::~UContentExCore() 
{
}

void UContentExCore::BeginPlay()
{
	// 800 / 600�� �ʹ� ����.
	// MainWindow.SetWindowScale({1280, 720});

	// �߿��Ѱ� ũ�Ⱑ �ƴ϶� ����
	//MainWindow.SetWindowPosition({500, 100});
	//                           1024                960
	MainWindow.SetWindowScale({ 1280.0f/* * 1.5f*/, 720.0f/* * 1.5f*/ });
	MainWindow.SetWindowPosition({ 100/* * 1.5f*/, 0/* * 1.5f*/ });
	// MainWindow.CursorOff();
	// 1200 

	// 800 16

	UEngineCore::BeginPlay();
	// D:\Project\GM\WIn\App
	UEngineDirectory NewDir;
	NewDir.MoveToSearchChild("ContentsResources");

	UEngineSound::SetGlobalVolume(0.5f);

	// �̹��� �ε�
	{
		std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);

		// �������� ��Ģ�� ���Ұų�.
		for (UEngineFile& File : NewList)
		{
			UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
		}

		UEngineResourcesManager::GetInst().CuttingImage("TestPlayer_Right.png", 5, 8);
		UEngineResourcesManager::GetInst().CuttingImage("TestPlayer_Left.png", 5, 8);
		UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("PlayLevel\\TestFolderAnimation"));

		std::shared_ptr<UWindowImage> Rot = UEngineResourcesManager::GetInst().FindImg("Dir.png");
		std::shared_ptr<UWindowImage> Mask = UEngineResourcesManager::GetInst().FindImg("Dir_Mask.bmp");
		Rot->SetRotationMaskImage(0, Mask, 0);
	}

	// �̹��� �ε�
	{
		std::list<UEngineFile> NewList = NewDir.AllFile({ ".wav", ".mp3" }, true);
		// �������� ��Ģ�� ���Ұų�.
		for (UEngineFile& File : NewList)
		{
			UEngineSound::Load(File.GetFullPath());
		}


	}


	// ���ν��� ���⼭ �ε��Ҽ��� �ִ�.

	// �츮�� �����ϴ°� Level
	CreateLevel<UTestLevel>("Test");
	CreateLevel<UTestTitleLevel>("Title");
	CreateLevel<UTestPlayLevel>("Play");
	CreateLevel<USoftRenderingLevel>("SoftRendering");
	ChangeLevel("SoftRendering");
}

void UContentExCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}


void UContentExCore::WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath)
{
	UEngineDirectory NewDir;
	NewDir.MoveToSearchChild("ContentsResources");

	_OutWindowTitle = "TestMyTitle";

	std::string IconPath = NewDir.AppendPath("Icon.ico");
	_SmallIconPath = IconPath;
}