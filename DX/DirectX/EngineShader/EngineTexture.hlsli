#define TextureSet(Name, Slot) Texture2D Name : register(t##Slot##); SamplerState Name##_Sampler : register(s##Slot##);

// ## ġȯ�� �� ����

#define Sampling(Name, TEXCOORD) Name##.Sample(##Name##_Sampler, ##TEXCOORD##.xy);

// HLSL�� �����ΰ� 
// C++ �������� ���� ġȯ