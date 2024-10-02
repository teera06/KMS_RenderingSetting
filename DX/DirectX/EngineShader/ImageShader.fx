// 쉐이더는 기본적으로
// hlsl이라는 전혀 다른 언어를 사용
// 쉐이더 뒤쪽에는 버텍스 _VS
// 픽셀 _PS
#include "EngineShaderBase.hlsli"

// 리턴할 구조체
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

// 상수버퍼라고 하는 인터페이스와 전용 문법을 이용해야만
// 다이렉트에 넣어줄수 있습니다.

// 커팅 데이터
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

// 텍스처는 상수버퍼와 슬롯을 공유하지 않는다.
// b0 buffer 0번 슬롯
// t0 texture 0번 슬롯
// s0 Samlper 0번 슬롯

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
