// ���̴��� �⺻������
// hlsl�̶�� ���� �ٸ� �� ���
// ���̴� ���ʿ��� ���ؽ� _VS
// �ȼ� _PS
#include "EngineShaderBase.hlsli"

// ������ ����ü
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
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

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

TextureSet(Image, 0);

cbuffer ReSultColorValue : register(b10)
{
    float4 PlusColor;
    float4 MulColor;
    float4 AlphaColor;
}

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);

    if (0>=Out.COLOR.a)
    {
        clip(-1);
    }
    
    Out.COLOR.xyz += PlusColor.xyz;
    Out.COLOR.wyzx *= MulColor.xyz;
    
    return Out;

}
