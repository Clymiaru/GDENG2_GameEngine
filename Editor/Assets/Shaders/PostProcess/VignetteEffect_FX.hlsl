cbuffer b_EffectData : register(b0)
{
	float4 EffectColor;
	float2 EffectCenterPosition;
	float2 IntensitySmoothness;
};

Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

struct PSInput
{
	float4 Position: SV_Position;
	float2 TexCoord : TexCoord;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	float2 uv = input.TexCoord.xy + EffectCenterPosition.xy;

	uv *=  1.0 - uv.yx;

	float vignette = uv.x * uv.y * IntensitySmoothness.x;

	vignette = pow(vignette, IntensitySmoothness.y);
	
	float4 color = t_Frame.Sample(s_FrameSampler, input.TexCoord) *
					EffectColor * vignette;
	return color;
}
