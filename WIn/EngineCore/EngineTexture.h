#pragma once

//#include "ThirdParty\DirectXTex\inc\DirectXTex.h"
// �������� ������ ���������ɰ� Ŭ������ �������� ���õ� ���
class UEngineTexture
{
public:
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

private:
	//*
};

