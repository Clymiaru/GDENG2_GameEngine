Texture2D tex;

SamplerState splr;

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
};

float4 PSMain(const PSInput input) : SV_TARGET
{
	const float4 color = tex.Sample(splr, input.TexCoord);
	return color;
}