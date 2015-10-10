cbuffer externalData : register(b0)
{
	matrix   view;
	matrix   projection;
	float4x4 transforms[1000];
	float    time;
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
	float  depth		: TEXCOORD1;
	float  time			: TEXCOORD2;
};

VertexToPixel main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
	VertexToPixel output;

	matrix world = transforms[instanceID];

	output.position = mul(float4(input.position, 1.0f), world);

	output.depth = output.position.z / output.position.w;

	float curvex = (sin((time*.0157 + output.depth)*.022) + cos((time*.0157 + output.depth)*.055)) * 2.0;
	float curvey = (cos((time*.0157 + output.depth)*.033) + -sin((time*.0157 + output.depth)*.077));
	/*matrix depthDistortion = { cos(output.depth*.1), -sin(output.depth*.1), 0.0, 0.0,
	sin(output.depth * .1), cos(output.depth*.1), 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 };*/

	matrix depthDistortion = { 1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		curvex, curvey, 0.0, 1.0 };

	/*matrix depthDistortion = { 1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 };*/

	output.position = mul(output.position, depthDistortion);

	output.position = mul(mul(output.position, view), projection);

	output.normal = mul(input.normal, (float3x3)mul(world, depthDistortion));
	output.uv = input.uv;
	output.time = time;

	return output;
}