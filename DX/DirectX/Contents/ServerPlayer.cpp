#include "PreCompile.h"
#include "ServerPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "SamCore.h"
#include "Packets.h"

AServerPlayer::AServerPlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ptr->SetupAttachment(Root);

	SetRoot(Root);

	SetActorScale3D({ 150.0f, 150.0f ,150.0f });

	
}

AServerPlayer::~AServerPlayer() 
{
}

void AServerPlayer::BeginPlay()
{
	AActor::BeginPlay();
	// ���÷��̾ ���� �����ϴ� �÷��̾�����
	// �ٸ� ������ �÷��̾����� 
	if (true)
	{
		InputOn();
	}
}

void AServerPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// �÷��̾ ��Ʈ�ѵ� �ϸ鼭
	// ���� �÷����ϴ� �÷��̾� => Ű ������ �����̰�
	
	// ������ ������ ������

	// ���÷��̾ ���� �����ϴ� �÷��̾�����
	// �ٸ� ������ �÷��̾����� 


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

	if (false == IsNetInit())
	{
		// ��Ʈ��ũ ����غ� ���� �ȵ� ������Ʈ��.
		if (nullptr != USamCore::Net)
		{
			InitNet(USamCore::Net);
		}
	}

	static float FrameTime = 1.0f / 60.0f;
	static float CurTime = FrameTime;

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Send(Packet);
		CurTime += FrameTime;
	}

	// ��������
}
