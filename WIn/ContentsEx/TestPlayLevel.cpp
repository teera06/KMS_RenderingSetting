#include "TestPlayLevel.h"
#include "TestPlayer.h"
#include "BackGroundMap.h"
#include <EngineCore\EngineCore.h>
#include "TestMonster.h"
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineSerializer.h>
#include <EngineBase\EngineFile.h>

UTestPlayLevel::UTestPlayLevel()
{
}

UTestPlayLevel::~UTestPlayLevel()
{
}

void UTestPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UEngineDirectory NewDir;
	NewDir.MoveToSearchChild("ContentsResources");
	NewDir.Move("Save");

	{
		std::string Text = "�ȳ��ϼ��� ��������";
		std::string Text2 = "�׷����� ȣȣȣȣȣ";

		UEngineSerializer Ser;
		Ser << Text;
		Ser << Text2;

		UEngineFile NewFile = NewDir.NewFile("AAAAAAA.txt");
		NewFile.Open(IOOpenMode::Write, IODataType::Text);
		NewFile.Save(Ser);

		int a = 0;
	}

	{
		std::string Text;
		std::string Text2;

		UEngineSerializer Ser;

		UEngineFile NewFile = NewDir.NewFile("AAAAAAA.txt");
		NewFile.Open(IOOpenMode::Read, IODataType::Text);
		NewFile.Load(Ser);

		Ser >> Text;
		Ser >> Text2;


		int a = 0;
	}




	Map = SpawnActor<ABackGroundMap>();
	Map->SetMapImage("Stage1Map.png");
	Map->SetColMapImage("Stage1Map_Col.png");
	Map->SwitchDebug();

	{
		ATestPlayer* NewActor = SpawnActor<ATestPlayer>();
		NewActor->SetName("Player");
		NewActor->SetActorLocation({ 500, 0 });

		// ���� �̹���� �������� �ʽ��ϴ�.
		// UContentsHelper::MainPlayer = NewActor;
	}

	// Foot_1_1.wav
	//BGMPlayer = UEngineSound::SoundPlay("Foot_1_1.wav");
	// BGMPlayer.Loop();
	// BGMPlayer = UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	// BGMPlayer.Off();
}

void UTestPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_F3))
	{
		GEngine->ChangeLevel("Title");
		// BGMPlayer.OnOffSwitch();
	}


	FVector Pos = GetCameraPos();

	if (0.0f >= Pos.X)
	{
		Pos.X = 0.0f;
	}

	if (0.0f >= Pos.Y)
	{
		Pos.Y = 0.0f;
	}

	FVector ImageScale = Map->GetImageScale();

	// ghk
	if (Pos.X >= ImageScale.X - GEngine->MainWindow.GetWindowScale().X)
	{
		Pos.X = ImageScale.X - GEngine->MainWindow.GetWindowScale().X;
	}

	if (true == UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->MainWindow.Off();
	}
	

	SetCameraPos(Pos);
}

void UTestPlayLevel::LevelStart(ULevel* _Level)
{
	// ���⼭ ���ҽ��� �ε��ϰ�
	// ���͵� ���⼭ �����
	int a = 0;
}
void UTestPlayLevel::LevelEnd(ULevel* _Level)
{
	// ���ҽ��� ������.
	// ���͸� �����Ѵ�.
	int a = 0;
}