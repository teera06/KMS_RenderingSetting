#pragma once
#include "DirectXHelper.h"
// 3D로 그려지는 점은 위치만 가질 필요가 없다.
// 

class UVertexLayOutInfo
{
public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	UINT OffsetSize = 0;

	void AddInputLayOut(
		LPCSTR _SemanticName,
		DXGI_FORMAT _Format,
		UINT _SemanticIndex = 0,
		UINT _InputSlot = 0,
		UINT _AlignedByteOffset = -1,
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
		UINT _InstanceDataStepRate = 0
	)
	{
		D3D11_INPUT_ELEMENT_DESC Desc;
		Desc.SemanticName = _SemanticName;
		Desc.SemanticIndex = _SemanticIndex;
		Desc.Format = _Format;

		Desc.InputSlot = _InputSlot;
		Desc.AlignedByteOffset = _InputSlot;

		// 자동 계산
		if (-1 == _AlignedByteOffset)
		{
			Desc.AlignedByteOffset += OffsetSize;
		
		}

		OffsetSize += UDirectXHelper::DirectFormatsize(_Format);

		Desc.InputSlotClass = _InputSlotClass;
		Desc.InstanceDataStepRate = _InstanceDataStepRate;

		Descs.push_back(Desc);
	}	
};

struct FEngineVertex
{
public:
	static UVertexLayOutInfo Info;

	float4 POSITION;
	float4 TEXCOORD;
};

