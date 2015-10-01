

cbuffer externalData : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

struct VertexShaderInput
{
    float3 position		: POSITION;     // XYZ position
    float2 uv		    : TEXCOORD;     // tex coord
    float3 normal       : NORMAL;       // normal
};

struct VertexToPixel
{

    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
    float3 normal       : NORMAL;
	float  depth		:TEXCOORD1;
};


VertexToPixel main(VertexShaderInput input)
{
    VertexToPixel output;

    matrix worldViewProj = mul(mul(world, view), projection);

    output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.normal = mul(input.normal, (float3x3)world);
    output.uv = input.uv;
	output.depth = output.position.z / output.position.w;
    
    return output;
}