#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsEnum.h"
#include <EngineCore/SpriteInstancingRender.h>

std::string APlayer::RendererName = "Renderer";

void Test(int Value)
{

}

APlayer::APlayer() 
{


	// 크자이공부
	// 부
	// 부모행렬이란?
	// 부모의 world행렬을 말합니다.

	// GetWorld()->GetMainCamera();

	// 생성자에서 당연히
	// SETWORLD이런게 호출된 상태로 사용될수 없다.
	// 플레이먼트 뉴가 있습니다.
	// 지연생성
	
	// 얼록케이터방식이 있을수 있습니다.

	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackRenderer->SetScale(FVector(100.0f, 100.0f, 100.0f));
	BackRenderer->SetupAttachment(Root);
	BackRenderer->SetOrder(-10);

	// 이름이 같아도 터진다.
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetScale(FVector(100.0f, 100.0f, 100.0f));
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(-10);
	Renderer->SetPivot(EPivot::BOT);

	ChildRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ChildRenderer->SetupAttachment(Root);
	ChildRenderer->SetScale(FVector(100.0f, 100.0f, 100.0f));
	ChildRenderer->SetOrder(-10);
	ChildRenderer->AddPosition({ -200.0f, 0.0f, 0.0f });

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale(FVector(100.0f, 300.0f, 100.0f));
	// 콜리전은 무조건 오더를 지정해줘야 한다.
	Collision->SetCollisionGroup(ECollisionOrder::Player);
	// Collision->SetCollisionType(ECollisionType::CirCle);
	Collision->SetCollisionType(ECollisionType::Rect);

	float Y = 0.0f;
	float X = 0.0f;

	//for (size_t i = 0; i < 3000; i++)
	//{
	//	USpriteRenderer* TestRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	//	if (0 == i % 50)
	//	{
	//		Y += 1.0f;
	//		X = 0.0f;
	//	}

	//	TestRenderer->SetPosition({ -300.0f + X + (i % 50) * 5.0f, 200.0f + -Y * 30.0f, 1.0f });
	//	TestRenderer->SetScale({100.0f, 100.0f, 1.0f});
	//	TestRenderer->SetSprite("CharIdle0.png");
	//	TestRenderer->SetupAttachment(Root);
	//	TestRenderer->SetOrder(ERenderOrder::Test);
	//}


	SetRoot(Root);

	InputOn();
}

APlayer::~APlayer() 
{
}

void APlayer::BeginPlay()
{
	// GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderOrder::Test);


	UEngineSerializer Ser;

	Ser << this;

	Super::BeginPlay();

	// SetActorScale3D(FVector(100.0f, 100.0f, 100.0f));

	// 내부에서 샘플러도 같이 찾을
	Renderer->SetSprite("CharIdle0.png");
	ChildRenderer->SetSprite("CharIdle0.png");
	
	BackRenderer->SetOrder(0);

	//Renderer->CreateAnimation("Die", "Die");
	//Renderer->CreateAnimation("Idle", "Idle");
	//Renderer->CreateAnimation("Jump", "Jump");
	//Renderer->CreateAnimation("Run", "Run", 0.1f);

	std::vector<std::shared_ptr<URenderer>> Renders = GetComponentToClass<URenderer>();

	StateInit();

	// Renderer->SetAutoSize(3.0f, true);
	// Renderer->SetOrder(ERenderOrder::Player);
}

void APlayer::Tick(float _DeltaTime)
{

	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	Renderer->SetOrder(1);

	// 그라비티


	Collision->CollisionStay(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);

	Collision->CollisionExit(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	VertexPlus.Y += _DeltaTime;

	Renderer->SetVertexUVPlus(VertexPlus);

	DebugMessageFunction(_DeltaTime);
}

void APlayer::DebugMessageFunction(float _Delta)
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		float4 WorldMousePos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(GEngine->EngineWindow.GetScreenMousePos());
		float4 PlayerPos = GetActorLocation();

		float4 Dir = WorldMousePos - PlayerPos;

		std::string Msg = std::format("Deg : {}\n", std::to_string(Dir.RightVectorToAngle2DDeg()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Frame : {}\n", 1.0f / _Delta);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}