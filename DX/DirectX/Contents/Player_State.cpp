#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Camera.h>

//void Function(URenderer* Renderer)
//{
//	Renderer->ChangeAnimation("Idle");
//}

void APlayer::StateInit()
{
	// 스테이트 만들고
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Jump");
	State.CreateState("Run");

	// 함수들 세팅하고
	//		int a = 0;
	//	});


	// 즉석 함수
	// = [ 람다캡쳐 Renderer]
	// {
	//    함수 내용
	// }
	
	// 람다캡처의 내용안에 =을 쓰면
	// 현재 스택에서 사용가능한 복사본을 만든다.
	// 메모리를 할당해서 Renderer를 같은 이름으로 복사한다.

	State.SetStartFunction("Idle", [this]()
		{
			// this->Renderer->ChangeAnimation("Idle");
		});

	State.SetUpdateFunction("Idle", [=](float _Delta)
		{
			if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
			{
				State.ChangeState("Run");
				return;
			}

			if (true == IsPress(VK_SPACE))
			{
				State.ChangeState("Jump");
				return;
			}
		});


	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));

	// 점프 파워를 넣는다.

	State.SetStartFunction("Jump", [=]()
		{
			// 점프파워를 높인다.
			JumpPower = float4(0.0f, 900.0f, 0.0f);
		});

	State.SetUpdateFunction("Jump", [=](float _Delta)
		{
			Gravity(_Delta);
			// 중력이 깍아먹는다는 개념으로 만들수도 있고
			AddActorLocation((JumpPower + GravityValue) * _Delta);
		});


	// 체인지
	State.ChangeState("Idle");
}


void APlayer::Gravity(float _DeltaTime)
{
	GravityValue += float4(0.0f, -1000.0f, 0.0f) * _DeltaTime;
}

void APlayer::Die(float _Update)
{

}

void APlayer::Jump(float _Update)
{
	int a = 0;
}


void APlayer::Run(float _DeltaTime)
{
	//if (true == Renderer->IsCurAnimationEnd())
	//{
	//	int a = 0;
	//}
	
	float Speed = 500.0f;

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == IsPress(VK_NUMPAD1))
	{
		AddActorRotation(float4{0.0f, 0.0f, 1.0f} * 360.0f * _DeltaTime);
		// Color.X += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD2))
	{
		AddActorScale3D(float4{ 1.0f, 1.0f, 1.0f } * _DeltaTime);
	}

	GetWorld()->GetMainCamera()->SetActorLocation(GetActorLocation() + float4{0.0f, 0.0f, -100.0f});

	if (true == IsPress(VK_NUMPAD4))
	{
		Destroy();
		Color.Y += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD5))
	{
		Color.Y -= _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD7))
	{
		Color.Z += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD8))
	{
		Color.Z -= _DeltaTime;
	}

	std::shared_ptr<UEngineTexture> Tex = UContentsConstValue::MapTex;

#ifdef _DEBUG
	if (nullptr == Tex)
	{
		MsgBoxAssert("이미지 충돌체크중 이미지가 존재하지 않습니다.");
	}
#endif

	float4 Pos = GetActorLocation();

	Pos /= UContentsConstValue::TileSize;
	Pos.Y = -Pos.Y;

	Color8Bit Color = Tex->GetColor(Pos, Color8Bit::Black);

	//if (Color != Color8Bit::Black)
	//{
	//	AddActorLocation(float4::Down * _DeltaTime * 100.0f);
	//}


}
