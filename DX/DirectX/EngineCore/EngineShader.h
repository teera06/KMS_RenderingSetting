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

	// �����ϵ� ���̴� �ڵ��� �ڵ�
	// �����ϵ� ������� ���⿡ ���ٰ� �ϰ� �����ϰų� Ư�� �Լ����� ����� �� �ʿ�
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;

	std::string EntryName = "None";
	EShaderType Type = EShaderType::NONE;

	void ShaderResCheck();
	
};

