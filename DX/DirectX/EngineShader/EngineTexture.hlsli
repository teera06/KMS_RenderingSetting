#define TextureSet(Name, Slot) Texture2D Name : register(t##Slot##); SamplerState Name##_Sampler : register(s##Slot##);

// ## 치환된 후 삭제

#define Sampling(Name, TEXCOORD) Name##.Sample(##Name##_Sampler, ##TEXCOORD##.xy);

// HLSL의 다파인과 
// C++ 디파인이 거의 치환