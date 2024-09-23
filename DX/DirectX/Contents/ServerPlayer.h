#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

// ���� :
class AServerPlayer : public AActor, public UNetObject
{
public:
	// constrcuter destructer
	AServerPlayer();
	~AServerPlayer();

	// delete Function
	AServerPlayer(const AServerPlayer& _Other) = delete;
	AServerPlayer(AServerPlayer&& _Other) noexcept = delete;
	AServerPlayer& operator=(const AServerPlayer& _Other) = delete;
	AServerPlayer& operator=(AServerPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

