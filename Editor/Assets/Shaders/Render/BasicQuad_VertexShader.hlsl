struct VSInput
{
	float4 Position: POSITION;
	float2 TexCoord : TEXCOORD;
};

struct VSOutput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

VSOutput VSMain(const VSInput input)
{
	VSOutput output;
	output.Position = input.Position;
	output.TexCoord = input.TexCoord;
	return output;
}