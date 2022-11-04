struct VSInput
{
	float4 Position: POSITION;
	float2 TexCoord : TEXCOORD;
	float4 Color: COLOR;
};

struct VSOutput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
	float4 Color: COLOR;
};

VSOutput VSMain(const VSInput input)
{
	VSOutput output;
	output.Position = input.Position;
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	return output;
}