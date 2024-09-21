#pragma once

//#include "ThirdParty\DirectXTex\inc\DirectXTex.h"
// 실제적인 랜더링 대상지정기능과 클리어등등 랜더링에 관련된 기능
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

