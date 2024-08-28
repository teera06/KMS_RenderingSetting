#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class UContentExCore : public UEngineCore
{
public:
	// constrcuter destructer
	UContentExCore();
	~UContentExCore();

	// delete Function
	UContentExCore(const UContentExCore& _Other) = delete;
	UContentExCore(UContentExCore&& _Other) noexcept = delete;
	UContentExCore& operator=(const UContentExCore& _Other) = delete;
	UContentExCore& operator=(UContentExCore&& _Other) noexcept = delete;

protected:
	void WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

