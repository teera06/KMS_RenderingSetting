#pragma once
#include <EngineCore\Actor.h>

// Ό³Έν :
class ATestTitleLogo : public AActor
{
public:
	// constrcuter destructer
	ATestTitleLogo();
	~ATestTitleLogo();

	// delete Function
	ATestTitleLogo(const ATestTitleLogo& _Other) = delete;
	ATestTitleLogo(ATestTitleLogo&& _Other) noexcept = delete;
	ATestTitleLogo& operator=(const ATestTitleLogo& _Other) = delete;
	ATestTitleLogo& operator=(ATestTitleLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

