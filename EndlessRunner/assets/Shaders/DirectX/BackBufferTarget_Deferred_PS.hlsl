
struct PixelInput
{
	float3 position		: POSITION;
	float2 uv		    : TEXCOORD;
};

Texture2D		txDiffuse : register(t0);
Texture2D		txNormal  : register(t1);
SamplerState	samLinear : register(s0);

float4 main( PixelInput input ) : SV_TARGET
{
	float4 diffuse = txDiffuse.Sample(samLinear, input.uv);

	float4 normalSampled = txNormal.Sample(samLinear, input.uv);

	float3 normal = normalSampled.xyz;
	float  depth = normalSampled.w;

	float4 ambientLight = float4(0.2f, 0.2f, 0.2f, 1.0f);
	float3 lightDir = float3(0.0f, 1.0f, 0.0f);
	float4 lightDiffuse = float4(0.6f, 0.6f, 0.6f, 1.0f);
	float3 color;

	color = diffuse * ambientLight;
	float diffuseValue = dot(lightDir, normal);
	//diffuseValue = round((diffuseValue+ .5) * 2.0) / 3;
	color += saturate(diffuseValue * lightDiffuse * diffuse);

	//color *= (1 - depth*depth*.0001);
	//return (1-input.depth*input.depth*.0001);
	//return float4((1 + input.normal)*.5, 1.0);
	return float4(normal, 1.0); //float4(d, diffuse.a);
}