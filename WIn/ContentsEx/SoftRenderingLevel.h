#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class USoftRenderingLevel : public ULevel
{
public:
	// constrcuter destructer
	USoftRenderingLevel();
	~USoftRenderingLevel();

	// delete Function
	USoftRenderingLevel(const USoftRenderingLevel& _Other) = delete;
	USoftRenderingLevel(USoftRenderingLevel&& _Other) noexcept = delete;
	USoftRenderingLevel& operator=(const USoftRenderingLevel& _Other) = delete;
	USoftRenderingLevel& operator=(USoftRenderingLevel&& _Other) noexcept = delete;

protected:
	void PlayerControl(float _DeltaTime);
	void CameraControl(float _DeltaTime);

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;
	void Render(float _DeltaTime) override;


private:

};

