


struct InstanceData
{
	float4x4 world;
};


StructuredBuffer<InstanceData> InstanceBuffer;

struct PointLight
{
	float4 color;
	float  intensity;
	float3 position;
	float  range;
	float  attenConstant;
	float  attenLinear;
	float  attenQuadratic;
};

StructuredBuffer<PointLight> LightBuffer;


cbuffer externalData : register(b2)
{
	matrix		view;
	matrix		projection;
	float		distance;
};

struct VertexShaderInput
{
	float3 position		: POSITION;     // XYZ position
	float2 uv		    : TEXCOORD;     // tex coord
	float3 normal       : NORMAL;       // normal
	float3 tangent		: TANGENT;

};


struct PS_INPUT
{
	float4 position : SV_POSITION;
	uint   instanceID : TEXCOORD;
};

PS_INPUT main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{

	PS_INPUT output;

	matrix world = InstanceBuffer[instanceID].world;
	PointLight light = LightBuffer[instanceID];

	output.position = mul(float4(input.position * -light.range * 1.2, 1.0f), world);

	output.position = mul(output.position, mul(view, projection));
	output.instanceID = instanceID;

	return output;
}