
struct PS_INPUT
{
	float4 position : SV_POSITION;
	uint   instanceID : TEXCOORD;
};




float4 main( PS_INPUT input ) : SV_TARGET
{
	//PixelOutput output;

	float idAsFloat = ((float)input.instanceID + 1.0) / 256.0;
	
	//output.lightData = 

	return float4(1.0, 0.0, 0.0, 1.0);
}