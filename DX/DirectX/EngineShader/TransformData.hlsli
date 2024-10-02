// 트랜스폼 상수버퍼라는것으로 정의
// 상수버퍼는 16개까지 세팅 가능
// b0 슬롯에 넣겠다.
// register(b15) 까지
// 하지만 상수 버퍼에는 516kb 이상이 되면 세팅이 불가능
// 크기에 제한


cbuffer FTransfom : register(b10)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPostition;
    
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPostition;
    
    float4x4 ScalMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat; // ??
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
}

struct FTransform
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPostition;
    
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPostition;
    
    float4x4 ScalMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat; // ??
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};