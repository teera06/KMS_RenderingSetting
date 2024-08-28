#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "TestPlayer.h"

// Ό³Έν :
class ATestMonster : public AActor
{
public:
	// constrcuter destructer
	ATestMonster();
	~ATestMonster();

	// delete Function
	ATestMonster(const ATestMonster& _Other) = delete;
	ATestMonster(ATestMonster&& _Other) noexcept = delete;
	ATestMonster& operator=(const ATestMonster& _Other) = delete;
	ATestMonster& operator=(ATestMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* BodyCollision;
};

