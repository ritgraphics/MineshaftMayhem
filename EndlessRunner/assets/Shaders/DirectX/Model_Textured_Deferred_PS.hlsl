
cbuffer externalData : register(b0)
{
	float time;
};

Texture2D		txDiffuse : register(t0);
Texture2D		txNormal : register(t1);
SamplerState	samLinear : register(s0);


struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 worldPos		: POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float3 tangent		: TANGENT;
	float  depth        : TEXCOORD1;
};

struct PixelOutput
{
	float4 diffuse : SV_Target0;
	float4 normal :  SV_Target1;
	float4 worldPos : SV_Target2;
};

PixelOutput main(VertexToPixel input)
{

	PixelOutput output;

	// Sample from normal map
	float3 normalFromMap = txNormal.Sample(samLinear, input.uv).rgb * 2 - 1;

	// Calculate the TBN matrix to go from tangent to world space
	float3 N = input.normal;
	float3 T = normalize(input.tangent - N * dot(input.tangent, N));
	float3 B = cross(T, N);
	float3x3 TBN = float3x3(T, B, N);

	input.normal = normalize(mul(normalFromMap, TBN));


	output.normal = float4(input.normal, input.depth);

	float4 diffuse = txDiffuse.Sample(samLinear, input.uv);
	
	output.diffuse = diffuse;

	output.worldPos = float4(input.worldPos, 1.0);

	return output;
}