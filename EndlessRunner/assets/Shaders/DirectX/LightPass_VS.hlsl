
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


cbuffer externalData : register(b1)
{
	matrix		view;
	matrix		projection;
	matrix      world;
	float		distance;
};

struct VS_INPUT
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


PS_INPUT main(uint id : SV_VertexID /*VS_INPUT input*//*, uint instanceID : SV_InstanceID*/)
{
	PS_INPUT output;

	/*PointLight currentLight = LightBuffer[instanceID];
	float3 lightPos = currentLight.position * 5;*/

	/*matrix world2 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 4, 8, 1
	};

	matrix wvp = mul(world2, mul(view, projection));

	output.position =  mul(input.position, wvp);*/ //float4(input.position, 1.0);
	/*output.instanceID = instanceID;*/
	//Light geo stuff here



	float2 uv = float2((id << 1) & 2, id & 2);
	output.position = float4(uv, 0.0f, 1.0f);
	output.position.x = output.position.x * 2 - 1;
	output.position.y = output.position.y * -2 + 1;

	return output;
}