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
	uv *= 1.0f - uv.yx;
	float vig = uv.x * uv.y * 15.0f;
	vig = pow(abs(vig), 0.75f);

	const float4 color = tex.Sample(splr, input.TexCoord);
	return color * vig;
}