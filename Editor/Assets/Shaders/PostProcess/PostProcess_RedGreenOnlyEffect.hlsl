Texture2D tex;

SamplerState splr;

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
};

float4 PSMain(const PSInput input) : SV_TARGET
{
	float2 uv = input.TexCoord;

	uv *= 8.0f;
	uv = frac(uv);
	
	float4 color = tex.Sample(splr, input.TexCoord);

	if ((uv.x >= 0.0f && uv.x < 0.5f &&
		uv.y >= 0.0f && uv.y < 0.5f) ||
		(uv.x >= 0.5f && uv.x < 1.0f &&
		uv.y >= 0.5f && uv.y < 1.0f))
	{
		color.b = 0.0f;
	}
	else
	{
		color.r = 0.0f;
	}
	
	return color;
}