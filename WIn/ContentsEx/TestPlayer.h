#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

// FSM�� ���ؼ� �˾ƺ���.
// �ѹ��� �Ѱ��� ���¸��� ������.
// �÷��̾ �ѹ��� 1���� �Լ����� �����Ѵ�.

// ���� :
class ATestPlayer : public AActor
{
private:
	static ATestPlayer* MainPlayer;

public:
	static ATestPlayer* GetMainPlayer();

	// constrcuter destructer
	ATestPlayer();
	~ATestPlayer();

	// delete Function
	ATestPlayer(const ATestPlayer& _Other) = delete;
	ATestPlayer(ATestPlayer&& _Other) noexcept = delete;
	ATestPlayer& operator=(const ATestPlayer& _Other) = delete;
	ATestPlayer& operator=(ATestPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// �� ���¸��� ������ ���� ���� ����Ǿ�� �Ѵ�.
	void DirCheck();

	std::string GetAnimationName(std::string _Name);

	// ���� �ֿ� ������Ʈ
	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	// ���� �Լ���
	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Run(float _DeltaTime);
	void Fly(float _DeltaTime);

	// ���� ���� �Լ���
	void IdleStart();
	void RunStart();
	void JumpStart();

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";

private:
	UCollision* BodyCollision = nullptr;

	UImageRenderer* PetRenderer = nullptr;
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* DirRenderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	float AlphaTime = 0.0f;
	bool Dir = false;

	float FreeMoveSpeed = 1000.0f;

	// bool IsGravity = true;
	// y�� �������� �ʴ´�.
	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 500.0f;
	float MoveMaxSpeed = 500.0f;
	void AddMoveVector(const FVector& _DirDelta);

	FVector GravityAcc = FVector::Down * 2000.0f;
	FVector GravityVector = FVector::Zero;


	FVector JumpPower = FVector::Up * 1000;
	FVector JumpVector = FVector::Zero;
	// ���� ���� ��� ������ ��
	FVector LastMoveVector = FVector::Zero;

	bool IsMove = false;
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;

	// ���� ������Ʈ�� ���°� �ƴմϴ�.
	// �̵�
	void CalLastMoveVector(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalJumpVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
	void GroundUp();
};

