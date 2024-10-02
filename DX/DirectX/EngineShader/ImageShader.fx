// ���̴��� �⺻������
// hlsl�̶�� ���� �ٸ� �� ���
// ���̴� ���ʿ��� ���ؽ� _VS
// �ȼ� _PS
#include "EngineShaderBase.hlsli"

// ������ ����ü
struct ImageVSOutPut
{
    float4 POSITION : SV_Position;
    float4 TEXCOORD : TEXCOORD;
};

// ������۶�� �ϴ� �������̽��� ���� ������ �̿��ؾ߸�
// ���̷�Ʈ�� �־��ټ� �ֽ��ϴ�.

// Ŀ�� ������
cbuffer FCuttingData : register(b2)
{
    float4 CuttingPosition;
    float4 CuttingSize;
    float4x4 PivoMat;
}

cbuffer FVertexUV : register(b3)
{
    float4 PlusUV;
}

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    
    // World
    
    float4x4 PivotWorld = mul(World, PivoMat);
    
    Out.POSITION = mul(_Input.POSITION, PivotWorld);
    Out.POSITION = mul(Out.POSITION, View);
    Out.POSITION = mul(Out.POSITION, Projection);
    
    Out.TEXCOORD.x = (_Input.TEXCOORD.x * CuttingSize.x) + CuttingPosition.x;
    Out.TEXCOORD.y = (_Input.TEXCOORD.y * CuttingSize.y) + CuttingPosition.y;
    
    Out.TEXCOORD.x += CuttingSize.x * PlusUV.x;
    Out.TEXCOORD.y += CuttingSize.y * PlusUV.y;
    
    
    return Out;
}

// �ؽ�ó�� ������ۿ� ������ �������� �ʴ´�.
// b0 buffer 0�� ����
// t0 texture 0�� ����
// s0 Samlper 0�� ����