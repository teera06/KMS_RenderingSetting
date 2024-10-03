#pragma once

class UEngineVertexBuffer;
class UEngineIndexBuffer;

class URenderUnit;
class URenderer;
class UEngineMesh : public UEngineResources<UEngineMesh> 
{
	friend URenderUnit;
	friend URenderer;

public:
	// constrcuter destructer
	UEngineMesh();
	~UEngineMesh();

	// delete Function
	UEngineMesh(const UEngineMesh& _Other) = delete;
	UEngineMesh(UEngineMesh&& _Other) noexcept = delete;
	UEngineMesh& operator=(const UEngineMesh& _Other) = delete;
	UEngineMesh& operator=(UEngineMesh&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	static std::shared_ptr<UEngineMesh> Create(std::string_view _MeshName, std::string_view _VertexName, std::string_view _IndexName)
	{
		std::shared_ptr<UEngineMesh> Res = CreateResName(_MeshName);
		Res->ResCreate(_VertexName, _IndexName);
		return Res;
	}

	void IndexDraw();

	// 인스턴싱
	void DrawIndexedInstanced(int _InstancingCount);
protected:
	void ResCreate(std::string_view _VertexName, std::string_view _IndexName);
private:
	// 버텍스 버퍼
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = nullptr; 

	// 인덱스 버퍼
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = nullptr;

	// 버텍스 버퍼 세팅
	void InputAssmbler1Setting(); 

	// 인덱스 버퍼 세팅
	void InputAssmbler2Setting();
};

