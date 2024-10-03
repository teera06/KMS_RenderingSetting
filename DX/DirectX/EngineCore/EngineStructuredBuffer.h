#pragma once
#include "EngineEnums.h"
#include "EngineBuffer.h"

class UEngineStructuredBufferSetter;
class UEngineStructuredBuffer : public UEngineResources<UEngineStructuredBuffer>, public UEngineBuffer
{
	friend UEngineStructuredBufferSetter;
public:
	// constrcuter destructer
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	// delete Function
	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineStructuredBuffer> CreateAndFind(EShaderType _Type, std::string_view _Name, UINT _ByteSize)
	{
		if (0 >= _ByteSize)
		{
			MsgBoxAssert("바이트 크기가 0보다 작은 상수버퍼는 만들수 없습니다.");
		}

		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == StructureBuffers.contains(_Type))
		{
			StructureBuffers[_Type];
		}

		if (false == StructureBuffers[_Type].contains(UpperName))
		{
			StructureBuffers[_Type][UpperName];
		}

		std::map<int, std::shared_ptr<UEngineStructuredBuffer>>& Buffers = StructureBuffers[_Type][UpperName];

		if (true == Buffers.contains(_ByteSize))
		{
			return Buffers[_ByteSize];
		}

		std::shared_ptr<UEngineStructuredBuffer> Res = CreateResUnName();
		Res->SetName(_Name);
		Res->Size = _ByteSize;
		Buffers[_ByteSize] = Res;
		return Res;
	}

	void Release();
	void Resize(int _Size);

	void ChangeData(const void* _Data, UINT _Size);


private:
	int Size = 0;

	static std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineStructuredBuffer>>>> StructureBuffers;

	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더 세팅해줄수 있는 권한

	UEngineSerializer Ser;

	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);
};

