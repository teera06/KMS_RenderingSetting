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

	// �ν��Ͻ�
	void DrawIndexedInstanced(int _InstancingCount);
protected:
	void ResCreate(std::string_view _VertexName, std::string_view _IndexName);
private:
	// ���ؽ� ����
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = nullptr; 

	// �ε��� ����
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = nullptr;

	// ���ؽ� ���� ����
	void InputAssmbler1Setting(); 

	// �ε��� ���� ����
	void InputAssmbler2Setting();
};

