#include "TestPlayer.h"
#include <EnginePlatform\EngineInput.h>
#include <EngineCore\EngineDebug.h>
#include "ContentsHelper.h"
#include <EngineBase\EngineDirectory.h>

//////////////////////////////// 이동관련


void ATestPlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void ATestPlayer::CalMoveVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		MoveVector = FVector::Zero;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		//static int Count = 0;
		//EngineDebug::OutPutDebugText(std::to_string(++Count));
		if (0.001 <= MoveVector.Size2D())
		{
			MoveVector += (-MoveVector.Normalize2DReturn()) * _DeltaTime * MoveAcc;
		}
		else {
			MoveVector = float4::Zero;
		}
	}

	if (MoveMaxSpeed <= MoveVector.Size2D())
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}
}

void ATestPlayer::CalJumpVector(float _DeltaTime)
{

}

void ATestPlayer::CalGravityVector(float _DeltaTime)
{
	GravityVector += GravityAcc * _DeltaTime;
	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
}

void ATestPlayer::MoveLastMoveVector(float _DeltaTime)
{
	// 카메라는 x축으로만 움직여야 하니까.
	GetWorld()->AddCameraPos(MoveVector * _DeltaTime);
	AddActorLocation(LastMoveVector * _DeltaTime);
}

void ATestPlayer::CalLastMoveVector(float _DeltaTime)
{
	// 제로로 만들어서 초기화 시킨다.
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
	LastMoveVector = LastMoveVector + GravityVector;
	LastMoveVector + JumpVector;
}

void ATestPlayer::GroundUp()
{
	while (true)
	{
		Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			AddActorLocation(FVector::Up);
		}
		else 
		{
			break;
		}
	}
}

void ATestPlayer::MoveUpdate(float _DeltaTime)
{
	CalMoveVector(_DeltaTime);
	CalGravityVector(_DeltaTime);
	CalLastMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
	GroundUp();
	// 이동을 하고 났더니 내가 땅에 처박혀 있을수 있죠?
}

////////////////////////////////

ATestPlayer* ATestPlayer::MainPlayer = nullptr;

ATestPlayer* ATestPlayer::GetMainPlayer()
{
	return MainPlayer;
}

ATestPlayer::ATestPlayer() 
{
}

ATestPlayer::~ATestPlayer() 
{
}

void ATestPlayer::BeginPlay()
{
	AActor::BeginPlay();

	MainPlayer = this;

	{
		Renderer = CreateImageRenderer(MarioRenderOrder::Player);
		Renderer->SetImage("TestPlayer_Right.png");
		Renderer->SetTransform({ {0,0}, {256, 256} });
		Renderer->CreateAnimation("Idle_Right", "TestPlayer_Right.png", 0, 0, 5.0f, true);
		Renderer->CreateAnimation("Idle_Left", "TestPlayer_Left.png", 0, 0, 0.1f, true);

		Renderer->CreateAnimation("Run_Right", "TestPlayer_Right.png", { 1, 2, 3 }, 1.0f, true);
		Renderer->CreateAnimation("Run_Left", "TestPlayer_Left.png", 1, 3, 1.0f, true);

		Renderer->CreateAnimation("Jump_Right", "TestPlayer_Right.png", 5, 5, 0.1f, true);
		Renderer->CreateAnimation("Jump_Left", "TestPlayer_Left.png", 5, 5, 0.1f, true);

		Renderer->ChangeAnimation("Idle_Right");
	}

	{
		DirRenderer = CreateImageRenderer(MarioRenderOrder::Player);
		DirRenderer->SetImage("Dir.png");
		// DirRenderer->SetTransform({ {0,0}, FVector{51, 93} * 3 });
		DirRenderer->SetTransform({ {0,0}, FVector{51, 93} * 3 });
	}

	{
		UImageRenderer* Renderer = CreateImageRenderer(MarioRenderOrder::Player);
		Renderer->SetImage("Dir.png");
		// DirRenderer->SetTransform({ {0,0}, FVector{51, 93} * 3 });
		Renderer->SetTransform({ {0,0}, FVector{50, 50} });
	}





	{
		PetRenderer = CreateImageRenderer(MarioRenderOrder::Player);
		PetRenderer->SetImage("TestPlayer_Right.png");
		PetRenderer->SetTransform({ {0,60}, {126, 126} });
	}

	// 일반적으로는 충돌이라는 시점을 따로둡니다.
	{
		BodyCollision = CreateCollision(MarioCollisionOrder::Player);
		BodyCollision->SetScale({10, 100});
		BodyCollision->SetColType(ECollisionType::CirCle);
	}

	
	StateChange(EPlayState::Idle);
}

void ATestPlayer::DirCheck()
{
	EActorDir Dir = DirState;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		// Renderer->ChangeAnimation(Name, true);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}
}


void ATestPlayer::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		//                             2        *  시간      * 500
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::Idle);
	}
}

void ATestPlayer::FreeMove(float _DeltaTime)
{
	FVector FreeMove = FVector::Zero;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		FreeMove += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		FreeMove += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		FreeMove += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		FreeMove += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(FreeMove * _DeltaTime);
	GetWorld()->AddCameraPos(FreeMove * _DeltaTime);

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
	}
}



std::string ATestPlayer::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;

}

void ATestPlayer::IdleStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void ATestPlayer::RunStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Run"));
	DirCheck();
}

void ATestPlayer::JumpStart()
{
	JumpVector = JumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();
}

void ATestPlayer::StateChange(EPlayState _State)
{
	// 이전상태와 지금 상태가 같지 않아
	// 이전에는 move 지금은 Idle
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Run:
			RunStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;


}

void ATestPlayer::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Run:
		Run(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}


}


void ATestPlayer::Idle(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		int a = 0;
	}

	// 왼쪽 오른쪽도 안되고 있고.
	// 여기서는 정말
	// 가만히 있을때만 어떻게 할지 신경쓰면 됩니다.
	if (true == UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::CameraFreeMove);
		return;
	}


	if (
		true == UEngineInput::IsPress(VK_LEFT) || 
		true == UEngineInput::IsPress(VK_RIGHT)
		)
	{
		StateChange(EPlayState::Run);
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	MoveUpdate(_DeltaTime);
}
void ATestPlayer::Jump(float _DeltaTime)
{

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	MoveUpdate(_DeltaTime);

	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		StateChange(EPlayState::Idle);
		return;
	}

}

void ATestPlayer::Run(float _DeltaTime)
{
	DirCheck();

	if (true == UEngineInput::IsFree(VK_LEFT) && UEngineInput::IsFree(VK_RIGHT))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddMoveVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddMoveVector(FVector::Right * _DeltaTime);
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}


	MoveUpdate(_DeltaTime);
}


void ATestPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	DirRenderer->AddScale(FVector{-100.0f, 0.0f} * _DeltaTime);
	DirRenderer->SetSortType(EImageSortType::Left);
	// DirRenderer->SetAngle(45);

	UEngineDirectory Dir;

	// UEngineDebug::DebugTextPrint("경로 : " + Dir.GetFullPath(), 30.0f);

	UEngineDebug::DebugTextPrint("경로 : " + std::to_string(UEngineInput::GetPressTime('Z')), 30.0f);

	StateUpdate(_DeltaTime);
}
