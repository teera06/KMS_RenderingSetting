#pragma once
#include "SceneComponent.h"
#include "RenderUnit.h"
// 
class URenderer : public USceneComponent, public std::enable_shared_from_this<URenderer>, public URenderUnit
{
	GENERATED_BODY(USceneComponent)
public:

	// constrcuter destructer
	URenderer();
	~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

protected:
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	

};

