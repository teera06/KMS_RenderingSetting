#pragma once
#include "EngineShader.h"

class UEngineVertexShader : public UEngineResources<UEngineVertexShader>, public UEngineShader
{
	friend UEngineMaterial;
public:
	// constrcuter destructer
	UEngineVertexShader();
	~UEngineVertexShader();

	// delete Function
	UEngineVertexShader(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader(UEngineVertexShader&& _Other) noexcept = delete;
	UEngineVertexShader& operator=(const UEngineVertexShader& _Other) = delete;
	UEngineVertexShader& operator=(UEngineVertexShader&& _Other) noexcept = delete;
	static std::shared_ptr<UEngineVertexShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _High = 5, UINT _Low = 0)
	{
		std::shared_ptr<UEngineVertexShader> Res = CreateResName(_Path);
		Res->ResLoad(_EntryPoint, _High, _Low);
		return Res;
	}


private:
	// 실제 셀이할 수 있는 쉐이더 핸들
	ID3D11VertexShader* ShaderPtr = nullptr;
	ID3D11InputLayout* LayOut = nullptr;

	void ResLoad(std::string_view _EntryPoint, UINT _High, UINT _Low);

	void Setting();
};

