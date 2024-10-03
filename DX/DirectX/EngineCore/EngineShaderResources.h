#pragma once
#include "EngineEnums.h"

class USetterBase : public UNameObject
{
public:
	EShaderType Type = EShaderType::NONE;
	int Slot = -1; // b0, b1, b2
};

class UEngineConstantBuffer;

// 상수 버퍼
class UEngineConstantBufferSetter : public  USetterBase
{
public:
	std::shared_ptr<UEngineConstantBuffer> Res;

	const void* CPUData = nullptr;
	UINT BufferSize = 0;

	void Setting();
	void Reset();
};

class UEngineStructuredBuffer;
// 구조체 버퍼
class UEngineStructuredBufferSetter : public USetterBase
{
public:
	std::shared_ptr<UEngineStructuredBuffer> Res;

	template<typename DataType>
	void PushData(const DataType& _Data)
	{
		PushData(&_Data, sizeof(_Data));
	}

	void PushData(const void* _Data, UINT _Size);

	UEngineSerializer Ser;
	UINT BufferSize = 0;

	void Setting();
	void Reset();
};

class UEngineTextureSetter : public USetterBase
{

public:
	std::shared_ptr<class UEngineTexture> Res;
	void Setting();
	void Reset();
	
};

class UEngineSamplerSetter : public  USetterBase
{
public:
	std::shared_ptr <class UEngineSampler> Res;
	void Setting();
	void Reset();
};

class UEngineShader;
class URenderUnit;
class URenderer;
class UEngineShaderResources 
{
	friend URenderUnit;
	friend UEngineShader;
	friend URenderer;
public:
	template<typename Value>
	void SettingConstantBuffer(std::string_view _Name, Value& _Data)
	{
		SettingConstantBuffer(_Name, &_Data, static_cast<UINT>(sizeof(Value)));
	}

	void SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size);

	bool IsConstantBuffer(std::string_view _Name);

	void SettingTexture(std::string_view _TexName, std::string_view _ImageName, std::string_view _SamperName);

	void SettingTexture(std::string_view _TexName, std::shared_ptr<UEngineTexture> _Texture, std::string_view _SamperName);


	void SettingAllShaderResources();

	void Reset();

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);

	// 상수 버퍼 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

	// textures
	std::map<EShaderType, std::map<std::string, UEngineTextureSetter>> Textures;

	// 샘플러
	std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>> Samplers;

	// 구조체 버퍼
	std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>> StructuredBuffers;


};

