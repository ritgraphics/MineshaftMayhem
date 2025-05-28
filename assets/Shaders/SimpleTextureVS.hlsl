
#include "Common.hlsli"

ConstantBuffer<DrawConstants> DrawConstantData : register(b1);
ConstantBuffer<CameraTransform> CameraTransformData : register(b0);
StructuredBuffer<ModelTransform> ModelTransformData : register(t0);

VertexPositionTextureOutput main(VertexPositionTextureInput input, uint instanceId : SV_InstanceID, uint vertexId: SV_VertexID)
{
    float3 position = input.Position;
    
    //position.y += sin(DrawConstantData.Time);
    VertexPositionTextureOutput output;
    output.Position = mul(mul(CameraTransformData.ViewProjection, ModelTransformData[instanceId].Model), float4(position, 1.0f));
    output.TexCoord = ModelTransformData[instanceId].TexCoord[vertexId];

    return output;
}

