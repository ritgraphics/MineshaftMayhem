
#include "Common.hlsli"

ConstantBuffer<DrawConstants> DrawConstantData : register(b1);
SamplerState LinearSampler : register(s0);
Texture2D gTexture : register(t1);

float4 main(VertexPositionTextureOutput input) : SV_Target
{
    float2 texCoord = input.TexCoord;
    float4 diffuse = gTexture.Sample(LinearSampler, texCoord);

    return diffuse;
}
