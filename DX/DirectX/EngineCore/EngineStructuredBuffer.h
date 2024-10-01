#pragma once
#include "EngineEnums.h"

class UEngineStructuredBufferSetter;
class UEngineStructuredBuffer : public UEngineResources<UEngineStructuredBuffer>
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
			MsgBoxAssert("����Ʈ ũ�Ⱑ 0���� ���� ������۴� ����� �����ϴ�.");
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




private:
	int Size = 0;

	static std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineStructuredBuffer>>>> StructureBuffers;

	ID3D10ShaderResourceView* SRV = nullptr; // ���̴� �������ټ� �ִ� ����

	UEngineSerializer Ser;
};
