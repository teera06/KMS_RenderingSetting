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
	//void Reset();
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
};

class UEngineTexturSetter : public USetterBase
{

public:
	std::shared_ptr<class UEngineTexture> Res;
	
};

class UEngineSamplerSetter : public  USetterBase
{


};

class EngineShaderResources 
{
public:
	template<typename Value>
	void SettingConstantBuffer(std::string_view _Name, Value& _Data)
	{
		SettingConstantBuffer(_Name, &_Data, static_cast<UINT>(sizeof(Value)));
	}

	void SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size);

	bool IsConstantBuffer(std::string_view _Name);
private:

	// 상수 버퍼 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

	// 구조체 버퍼
	std::map<EShaderType, std::map<std::string, UEngineStructuredBufferSetter>> StructureBuffers;

};

