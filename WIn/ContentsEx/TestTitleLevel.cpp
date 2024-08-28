#include "TestTitleLevel.h"
#include "TestTitleLogo.h"
#include "EngineCore\EngineCore.h"
#include "TestPlayLevel.h"

UTestTitleLevel::UTestTitleLevel() 
{
}

UTestTitleLevel::~UTestTitleLevel() 
{
}

void UTestTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	{
		// ���⼭ ��ġ�� ���������ٰ� �̳༮��ġ�� 0,0�ΰ� �ƴ���
		ATestTitleLogo* Logo = SpawnActor<ATestTitleLogo>();
	}


}
void UTestTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_F3))
	{
		GEngine->CreateLevel<UTestPlayLevel>("Play");
		GEngine->ChangeLevel("Play");
		// BGMPlayer.OnOffSwitch();
	}
}
void UTestTitleLevel::LevelStart(ULevel* _Level)
{
	GEngine->DestroyLevel("Play");

	int a = 0;
}
void UTestTitleLevel::LevelEnd(ULevel* _Level)
{
	int a = 0;
}