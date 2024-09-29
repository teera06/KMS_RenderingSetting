#pragma once

#include "EngineBuffer.h"


class UEngineVertexBuffer:public UEngineResources<UEngineVertexBuffer>, public UEngineBuffer
{
public:
	// constrcuter destructer
	UEngineVertexBuffer();
	~UEngineVertexBuffer();

	// delete Function
	UEngineVertexBuffer(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer(UEngineVertexBuffer&& _Other) noexcept = delete;
	UEngineVertexBuffer& operator=(const UEngineVertexBuffer& _Other) = delete;
	UEngineVertexBuffer& operator=(UEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertextType>
	static std::shared_ptr<UEngineVertexBuffer> Create(std::string_view _Name, const std::vector<VertextType> _Data)
	{
		std::shared_ptr<UEngineVertexBuffer> Res = CreateResName(_Name);
		Res->ResCreate(&_Data[0], static_cast<UINT>(sizeof(VertextType)), static_cast<UINT>(_Data.size()));
		
		
	}
private:
	
	UINT Size = 0;
	UINT Count = 0;
	UINT Offset = 0;

	void ResCreate(const void* _Data, UINT _Size, UINT _Count);

	void Setting();
};

