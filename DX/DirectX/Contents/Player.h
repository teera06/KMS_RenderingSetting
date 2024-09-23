#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineBase/EngineSerializer.h>

struct PlayerStatus
{
	int Hp;
	int Att;
};

// Ό³Έν :
class USpriteRenderer;
class APlayer : public AActor, public UEngineSerializeObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackRenderer;
	USpriteRenderer* Renderer;
	USpriteRenderer* ChildRenderer;
	UCollision* Collision;
	float4 Color;
	float4 GravityValue;

	static PlayerStatus Status;

	float4 JumpPower = {0.0f, 500.0f, 0.0f, 0.0f};

	void Serialize(UEngineSerializer& _Ser)
	{
	}

	void DeSerialize(UEngineSerializer& _Ser)
	{

	}

	///////////////////////// State
	void StateInit();

	void Die(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Run(float _DeltaTime);

	void Gravity(float _DetlaTime);

	void DebugMessageFunction(float _Delta);

	float4 VertexPlus;

	static std::string RendererName;
};

