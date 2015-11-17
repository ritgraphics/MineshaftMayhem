
cbuffer externalData : register(b0)
{
};


struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float  depth		: TEXCOORD1;
};

struct PixelOutput
{
	float4 diffuse : SV_Target0;
	float4 normal  : SV_Target1;
};


PixelOutput main(VertexToPixel input) : SV_TARGET
{
	PixelOutput output;


	input.normal = normalize(input.normal);

	output.normal = float4(input.normal, input.depth);
	
	output.diffuse = float4(0.25f, 0.25f, 0.25f, 1.0f);

	return output;
}