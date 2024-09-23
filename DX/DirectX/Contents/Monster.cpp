#include "PreCompile.h"
#include "Monster.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

AMonster::AMonster() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ptr->SetupAttachment(Root);


	UCollision* Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);


	SetRoot(Root);
	// ≥¿µŒ¡“.
	SetActorScale3D({150.0f, 150.0f ,150.0f });
}

AMonster::~AMonster() 
{
}

