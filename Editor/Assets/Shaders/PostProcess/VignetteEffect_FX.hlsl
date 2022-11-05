cbuffer b_EffectData : register(b0)
{
	float4 EffectColor;
	float2 EffectCenterPosition;
	float2 ScreenSize;
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
	float2 position = (input.Position.xy / ScreenSize) - 0.5f;
	float dist = length(position * float2(ScreenSize.x / ScreenSize.y, 1.0));

	float radius = 0.75;
	float softness = 0.02;

	float vignette = smoothstep(radius, radius - softness, dist);

	float4 color = t_Frame.Sample(s_FrameSampler, input.TexCoord);
	
	color.rgb = color.rgb - (1.0 - vignette);
	
	return color;
}