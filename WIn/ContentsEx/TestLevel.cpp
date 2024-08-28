#include "TestLevel.h"
#include <EnginePlatform\EngineInput.h>
#include <EnginePlatform\EngineWindow.h>
#include <EngineCore\EngineCore.h>
#include "BackGroundMap.h"

UTestLevel::UTestLevel() 
{
}

UTestLevel::~UTestLevel() 
{
}

void UTestLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGroundMap* Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1Map.png");
	Map->SetColMapImage("Stage1Map_Col.png");
	Map->SwitchDebug();

}

void UTestLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);


}

void UTestLevel::LevelStart(ULevel* _Level)
{
}

void UTestLevel::LevelEnd(ULevel* _Level)
{
}