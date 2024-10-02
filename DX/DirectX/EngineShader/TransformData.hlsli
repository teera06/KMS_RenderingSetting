// Ʈ������ ������۶�°����� ����
// ������۴� 16������ ���� ����
// b0 ���Կ� �ְڴ�.
// register(b15) ����
// ������ ��� ���ۿ��� 516kb �̻��� �Ǹ� ������ �Ұ���
// ũ�⿡ ����


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