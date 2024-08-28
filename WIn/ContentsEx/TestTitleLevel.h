#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class UTestTitleLevel : public ULevel
{
public:
	// constrcuter destructer
	UTestTitleLevel();
	~UTestTitleLevel();

	// delete Function
	UTestTitleLevel(const UTestTitleLevel& _Other) = delete;
	UTestTitleLevel(UTestTitleLevel&& _Other) noexcept = delete;
	UTestTitleLevel& operator=(const UTestTitleLevel& _Other) = delete;
	UTestTitleLevel& operator=(UTestTitleLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};

