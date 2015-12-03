
struct PixelInput
{
	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
};

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

Texture2D		txDiffuse : register(t0);
Texture2D		txNormal  : register(t1);
Texture2D		txWorld	  : register(t2);
Texture2D		txLight	  : register(t3);
SamplerState	samLinear : register(s0);


PointLight getLight(Texture2D lightIndices, SamplerState ss, float2 uv)
{
	float4 light = lightIndices.Sample(ss, uv);
	int index = 1;// ceil(light.r);
	if (index != 0) 
	{
		return LightBuffer[index-1];
	}
	else
	{
		PointLight nothing;
		nothing.color = lightIndices.Sample(ss, uv);//float4(1, 1, 1, 1);
		nothing.intensity = 0;
		nothing.position = float3(0, 0, 0);
		nothing.range = 100;
		nothing.attenConstant = 0;
		nothing.attenLinear = 0;
		nothing.attenQuadratic = 0;
		return nothing;
	};
}

float4 main( PixelInput input ) : SV_TARGET
{
	float4 diffuse = txDiffuse.Sample(samLinear, input.uv);
	float4 normalSampled = txNormal.Sample(samLinear, input.uv);
	float4 worldPos = txWorld.Sample(samLinear, input.uv);

	float3 normal = normalSampled.xyz;
	float  depth = normalSampled.w;

	float4 ambientLight = float4(0.2f, 0.2f, 0.2f, 1.0f);
	
	//point light
	PointLight light = getLight(txLight, samLinear, input.uv);
	float3 lightDir = normalize(light.position -  worldPos.xyz);
	float4 lightDiffuse = light.color;
	//attenuation
	float lightDist = (light.position - worldPos).x / (lightDir.x * light.range);
	float atten = saturate(1 - (lightDist * lightDist * light.attenQuadratic + lightDist * light.attenLinear + light.attenConstant));

	float4 color = diffuse * ambientLight; //ambientLight;
	float diffuseValue = dot(lightDir, normal) * atten;
	//diffuseValue = round((diffuseValue+ .5) * 2.0) / 3;
	color += saturate(diffuseValue * lightDiffuse * diffuse);

	color *= (1 - depth*depth*.0001);
	//return (1-input.depth*input.depth*.0001);
	//return float4((1 + input.normal)*.5, 1.0);
	//return float4(light.color.rgb, 1.0);
	return float4(color.rgb, diffuse.a); //float4(d, diffuse.a);
	
}

