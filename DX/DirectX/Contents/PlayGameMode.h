#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>

// Ό³Έν :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	std::atomic_int LoadingCount;
	static std::atomic<bool> PlayLevelLoading;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PlayLevelActorCreate();

private:
	std::vector<std::shared_ptr<UEngineThread>> LoadingThreads;
};

