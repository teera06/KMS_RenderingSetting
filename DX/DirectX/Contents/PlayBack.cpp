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

	// 내부에서 샘플러도 같이 찾을
	Renderer->SetSprite("Back.png");

	Renderer->SetAutoSize(1.0f, true);

	// Renderer->SetOrder(ERenderOrder::Back);
}

void APlayBack::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);
}