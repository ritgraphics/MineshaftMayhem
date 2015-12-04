
struct PS_INPUT
{
	float4 position : SV_POSITION;
	uint   instanceID : TEXCOORD;
};


struct PS_OUTPUT
{
	float4 lightData : SV_Target0;
};

PS_OUTPUT main( PS_INPUT input ) : SV_TARGET
{
	PS_OUTPUT output;

	float idAsFloat = ((float)input.instanceID + 1.0) / 256.0;
	
	output.lightData = float4(1.0, 0.0, 0.0, 1.0);

	return output;
}