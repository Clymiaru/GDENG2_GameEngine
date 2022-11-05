struct VSInput
{
	float4 Position : Position;
	float2 TexCoord : TexCoord;
};

struct VSOutput
{
	float4 Position : SV_Position;
	float2 TexCoord : TexCoord;
};

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.Position = input.Position;
	output.TexCoord = input.TexCoord;
	return output;
}