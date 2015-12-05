
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

cbuffer pixelData : register(b0)
{
	float width;
	float height;
};

struct PS_INPUT
{
	float4 position   : SV_POSITION;
	float4 center     : TEXCOORD1;
	PointLight light : TEXCOORD2;
};



//struct PS_OUTPUT
//{
//	float4 lightData : SV_Target0;
//};

Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txWorld : register(t2);

SamplerState samLinear : register(s0);

float4 main( PS_INPUT input ) : SV_TARGET
{
	/*PS_OUTPUT output;*/

	input.position.x = input.position.x / width;
	input.position.y = input.position.y / height;

	float4 worldPos = txWorld.Sample(samLinear, input.position.xy);
	float4 normal = txNormal.Sample(samLinear, input.position.xy);
	normal = normalize(normal * 2 - 1);
	float3 lightDir = normalize(input.center - worldPos.xyz);
	float4 lightDiffuse = input.light.color;
	//attenuation
	float lightDist = (input.center - worldPos).x / (lightDir.x * input.light.range);
	float atten = saturate(1 - (lightDist * lightDist * input.light.attenQuadratic + lightDist * input.light.attenLinear + input.light.attenConstant));

	float diffuseValue = saturate(dot(lightDir, normal)) * atten;
	float4 lightData = lightDiffuse * diffuseValue;

	return float4(lightData.xyz, 1.0);
}