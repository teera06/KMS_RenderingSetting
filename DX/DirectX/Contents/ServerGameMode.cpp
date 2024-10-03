#include "PreCompile.h"
#include "ServerGameMode.h"
#include "Player.h"
#include "PlayBack.h"
#include "Monster.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
//#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include "MyWidget.h"
#include "ServerPlayer.h"
#include "PlayGameMode.h"
#include "SamCore.h"
#include "Packets.h"
#include "OtherPlayer.h"

AServerGameMode::AServerGameMode() 
{
}

AServerGameMode::~AServerGameMode() 
{
	if (nullptr != USamCore::Net)
	{
		USamCore::Net->End();
		USamCore::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay() 
{
	Super::BeginPlay();
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	MainPlayer = GetWorld()->SpawnActor<AServerPlayer>("Player");
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AServerGameMode::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				USamCore::Net = std::make_shared<UEngineServer>();
				USamCore::Net->ServerOpen(30000, 512);

				// 여기에서 메인 플레이어한테 번호를 하나 줄겁니다.

				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

				ServerPacketInit(USamCore::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				USamCore::Net = std::make_shared<UEngineClient>();
				USamCore::Net->Connect(IP, PORT);

				USamCore::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						MainPlayer->SetObjectToken(_Token->GetObjectToken());

					});

				// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
				ClientPacketInit(USamCore::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			if (nullptr == USamCore::Net)
			{
				return;
			}

			// 다른 사람들한테 이 오브젝트에 대해서 알리고
			USamCore::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					// 여긴 주쓰레드니까.
					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}

					OtherPlayer->PushProtocol(_Packet);

					// OtherPlayer->SetActorLocation(_Packet->Pos);
				});


		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}