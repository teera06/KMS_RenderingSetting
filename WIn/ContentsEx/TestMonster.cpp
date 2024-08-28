#include "TestMonster.h"

ATestMonster::ATestMonster() 
{
}

ATestMonster::~ATestMonster() 
{
}

void ATestMonster::BeginPlay()
{
	AActor::BeginPlay();

	{
		UImageRenderer* Renderer = CreateImageRenderer(MarioRenderOrder::Player);
		Renderer->SetTransform({ {0,0}, {100, 100} });
		Renderer->SetImage("TestFolderAnimation");
	}

	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Monster);
		BodyCollision->SetScale({ 100, 100 });
		BodyCollision->SetColType(ECollisionType::Rect);
	}
}

void ATestMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//std::vector<UCollision*> Result;
	//if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	//{
	//	// 이런식으로 상대를 사용할수 있다.
	//	BodyCollision->Destroy();
	//	BodyCollision = nullptr;
	//	// BodyCollision = nullptr;
	//}

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(MarioCollisionOrder::Player, Result))
	{
		// 이런식으로 상대를 사용할수 있다.
		BodyCollision->SetActive(true, 1.0f);
		// BodyCollision = nullptr;
	}
	

	ATestPlayer* Player = ATestPlayer::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	FVector PlayerPos = Player->GetActorLocation();
	FVector MonsterPos = GetActorLocation();

	FVector MonsterDir = PlayerPos - MonsterPos;
	// MonsterDir.Y = 0.0f;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();

	AddActorLocation(MonsterDirNormal * _DeltaTime * 100.0f);

	// 플레이어를 알아야 한다.
	// 
}