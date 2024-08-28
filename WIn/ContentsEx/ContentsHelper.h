#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum class MarioRenderOrder
{
	Map,
	Monster,
	Player,
	Text,
};

enum class MarioCollisionOrder
{
	PlayerBullet,
	Monster,
	Player
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EPlayState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Run,
	Jump,
};



// Ό³Έν :
class UContentsHelper
{
public:
	static class ATestPlayer* MainPlayer;
	static std::shared_ptr<UWindowImage> ColMapImage;
	static FVector GetMousePos();

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

