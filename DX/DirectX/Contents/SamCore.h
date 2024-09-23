#pragma once
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineNet.h>

// Ό³Έν :
class UEngineNet;
class USamCore : public UserCore
{
public:
	// constrcuter destructer
	USamCore();
	~USamCore();

	// delete Function
	USamCore(const USamCore& _Other) = delete;
	USamCore(USamCore&& _Other) noexcept = delete;
	USamCore& operator=(const USamCore& _Other) = delete;
	USamCore& operator=(USamCore&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineNet> Net;

protected:
	void Initialize() override;

private:

};

