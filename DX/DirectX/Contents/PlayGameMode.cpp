#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBack.h"
#include "Monster.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
//#include <EngineCore/BlurEffect.h>
#include "MyWidget.h"

std::atomic<bool> APlayGameMode::PlayLevelLoading = true;

APlayGameMode::APlayGameMode() 
{
}

APlayGameMode::~APlayGameMode() 
{
}

class MonsterData 
{
public:
	int Att;
	int Hp;
};

class MySaveFile : public UEngineSerializeObject
{
public:
	ULevel* Test;
	std::string PlayerName;
	std::vector<int> Data;
	std::vector<std::vector<int>> TileData;

	void Serialize(UEngineSerializer& _Ser) override
	{
		// 저장순서랑 로드순서를 
		_Ser << PlayerName;
		_Ser << Data;
		_Ser << TileData;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		_Ser >> PlayerName;
		_Ser >> Data;
		_Ser >> TileData;
	}
};

void APlayGameMode::BeginPlay() 
{
	 PlayLevelActorCreate();

	GetWorld()->GetMainCamera()->DepthOn();

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Save");

		{
			std::vector<std::vector<int>> TileData = { {4,3, 2}, {5,6, 7}, {7,6, 7} };

			UEngineSerializer Ser;
			Ser << TileData;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Write, EIODataType::Binary);
			File.Save(Ser);
		}

		{
			MySaveFile SaveData;

			std::vector<std::vector<int>> TileData;
			UEngineSerializer Ser;

			UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
			File.Open(EIOOpenMode::Read, EIODataType::Binary);
			File.Load(Ser);

			Ser >> TileData;
		}
	}


	// GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
	// GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
	// GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
	// GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
	//GetWorld()->GetMainCamera()->GetCameraTarget()->AddEffect<UBlurEffect>();

	Super::BeginPlay();

	// SetThreadDescription(GetCurrentThread(), L"TestThread");


	int a = 0;
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	float4 Mouse = GEngine->EngineWindow.GetScreenMousePos();
	float4 UIPos = GetWorld()->GetUICamera()->ScreenPosToWorldPos(Mouse);
	UEngineDebugMsgWindow::PushMsg(std::format("UIMousePos : {}", UIPos.ToString()));

	//if (0 == LoadingCount)
	//{
	//	PlayLevelActorCreate();
	//	LoadingCount = 2000;
	//}

	if (UEngineInput::IsDown('I'))
	{
		GEngine->ChangeLevel("ServerLevel");

		int a = 0;
	}

}

void APlayGameMode::PlayLevelActorCreate()
{
	// 절대로 먼저 실행하면 안된다.

	UContentsConstValue::MapTex = UEngineTexture::FindRes("Back.png");
	UContentsConstValue::MapTexScale = UContentsConstValue::MapTex->GetScale();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, -360.0f, -100.0f));

	{
		MyWidget* Widget = CreateWidget<MyWidget>(GetWorld(), "Test");


		//// UI를 만들겠다.
		//// std::shared_ptr<UImage> Image = CreateWidget<UImage>(GetWorld(), "HpBar");
		//UImage* Image = CreateWidget<UImage>(GetWorld(), "HpBar");

		//// 자기자신이 자기자신을 std::shared_ptr<UImage>로 가지고 있어도 난다.

		//// 언리얼 따라한것
		//// 언리얼 안나옵니다.
		//Image->AddToViewPort(2);
		//Image->SetSprite("HPBar.png");
		//Image->SetAutoSize(0.5f, true);
		//Image->SetPosition({ -400, 300 });

		//UImage* Image0 = CreateWidget<UImage>(GetWorld(), "HpBar");

		//Image0->SetupAttachment(Image);
		//Image0->AddToViewPort(2);
		//Image0->SetWidgetScale3D({0.5f, 0.5f , 0.5f });

		//Image0->SetSprite("HPBar.png");


		//Image->SetUnHover([=]()
		//	{
		//		Image->SetSprite("HPBar.png");
		//		// UEngineDebugMsgWindow::PushMsg("Hover!!!");
		//	});

		//Image->SetHover([=]()
		//	{
		//		Image->SetSprite("Back.png");
		//		Image->SetAutoSize(1.0f, false);
		//		// UEngineDebugMsgWindow::PushMsg("Hover!!!");
		//	});

		//Image->SetDown([=]()
		//	{
		//		UEngineDebugMsgWindow::PushMsg("Down!!!");
		//	});

		// Image->SetScale({200, 200});

		// 화면에 떠야 한다.
		// Image->SetSprite("HPBar");
		// Image->SetScale();
	}

	{
		std::shared_ptr<APlayer> Actor = GetWorld()->SpawnActor<APlayer>("Player", EObjectOrder::Player);
		Actor->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	}

	{
		std::shared_ptr<AMonster> Actor = GetWorld()->SpawnActor<AMonster>("Monster", EObjectOrder::Monster);
		Actor->SetActorLocation({ 1040.0f, -360.0f, 200.0f });
	}

	{
		std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");

		float TileSize = UContentsConstValue::TileSize;
		float4 TexScale = UContentsConstValue::MapTexScale;
		float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };

		Back->SetActorScale3D(ImageScale);
		Back->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	}

}