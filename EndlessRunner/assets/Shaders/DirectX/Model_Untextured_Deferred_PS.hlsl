
cbuffer externalData : register(b0)
{
};

struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 worldPos		: POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float3 tangent		: TANGENT;
	float  depth : TEXCOORD1;
};

struct PixelOutput
{
	float4 diffuse : SV_Target0;
	float4 normal :  SV_Target1;
	float4 worldPos : SV_Target2;
};


PixelOutput main(VertexToPixel input) : SV_TARGET
{
	PixelOutput output;


	input.normal = normalize(input.normal);

	output.normal = float4(input.normal, input.depth);
	
	output.diffuse = float4(0.25f, 0.25f, 0.25f, 1.0f);

	output.worldPos = float4(input.worldPos, 1.0);

	return output;
}