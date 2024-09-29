#pragma once

class UEngineVertexBuffer;

class UEngineMesh : public UEngineResources<UEngineMesh> 
{

public:
	// constrcuter destructer
	UEngineMesh();
	~UEngineMesh();

	// delete Function
	UEngineMesh(const UEngineMesh& _Other) = delete;
	UEngineMesh(UEngineMesh&& _Other) noexcept = delete;
	UEngineMesh& operator=(const UEngineMesh& _Other) = delete;
	UEngineMesh& operator=(UEngineMesh&& _Other) noexcept = delete;

private:
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = nullptr;
};

