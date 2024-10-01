#pragma once

class URenderUnit;
class UEngineVertexBuffer;
class UEngineVertexShader;
class UEngineInputLayOut : UEngineResources<UEngineInputLayOut>
{
	friend URenderUnit;
public:
	// constrcuter destructer
	UEngineInputLayOut();
	~UEngineInputLayOut();

	// delete Function
	UEngineInputLayOut(const UEngineInputLayOut& _Other) = delete;
	UEngineInputLayOut(UEngineInputLayOut&& _Other) noexcept = delete;
	UEngineInputLayOut& operator=(const UEngineInputLayOut& _Other) = delete;
	UEngineInputLayOut& operator=(UEngineInputLayOut&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineInputLayOut> Create(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader)
	{
		std::shared_ptr<UEngineInputLayOut> Res = CreateResUnName();
		Res->
	}

private:
	ID3D11InputLayout* LayOut = nullptr;

	void ResCreate(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader);
	void Setting();

};

