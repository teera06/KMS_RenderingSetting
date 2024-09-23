#include "PreCompile.h"
#include "PlayBack.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

APlayBack::APlayBack() 
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetOrder(20);
	SetRoot(Renderer);
	InputOn();
}

APlayBack::~APlayBack() 
{
}

void APlayBack::BeginPlay()
{
	Super::BeginPlay();

	// SetActorScale3D(FVector(1280.0f, 720.0f, 100.0f));

	// ���ο��� ���÷��� ���� ã��
	Renderer->SetSprite("Back.png");

	Renderer->SetAutoSize(1.0f, true);

	// Renderer->SetOrder(ERenderOrder::Back);
}

void APlayBack::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);
}