#include "ContentExCore.h"

#include <EngineWindow\EngineInput.h>
#include <EngineWindow\WindowImage.h>
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
	// 800 / 600은 너무 작죠.
	// MainWindow.SetWindowScale({1280, 720});

	// 중요한건 크기가 아니라 비율
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