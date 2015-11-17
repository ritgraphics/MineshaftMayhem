
cbuffer externalData : register(b0)
{
	float time;
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

	output.diffuse = float4(sin(input.depth * .5)*.5 + .5, cos(input.depth * .5)*.5 + .5, -sin(input.depth *.5)*.5 + .5, 1.0f);

	return output;
}