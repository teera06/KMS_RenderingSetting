// hlsl에서 float4개의 집합인 자료형의 이름이 float4
// 그대로 쉐이더에서 사용할 수 있는 버텍스 구조체가 된다.

struct FEngineVertex
{
    float4 POSITION : POSITIONT;
    float4 TEXCOORD : TEXCOORD;
};