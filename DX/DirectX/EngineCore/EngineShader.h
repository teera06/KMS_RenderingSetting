#pragma once
#include "EngineEnums.h"
class UEngineShader
{
public:
	static void AutoCompile(UEngineDirectory _Dir);

	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	
protected:

	// 컴파일된 쉐이더 코드의 핸들
	// 컴파일된 결과물이 여기에 들어간다고 하고 세팅하거나 특정 함수들을 사용할 때 필요
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;

	std::string EntryName = "None";
	EShaderType Type = EShaderType::NONE;

	void ShaderResCheck();
	
};

