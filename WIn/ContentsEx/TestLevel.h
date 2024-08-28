#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class UTestLevel : public ULevel
{
public:
	// constrcuter destructer
	UTestLevel();
	~UTestLevel();

	// delete Function
	UTestLevel(const UTestLevel& _Other) = delete;
	UTestLevel(UTestLevel&& _Other) noexcept = delete;
	UTestLevel& operator=(const UTestLevel& _Other) = delete;
	UTestLevel& operator=(UTestLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;


private:

};

