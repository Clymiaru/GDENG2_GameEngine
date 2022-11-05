cbuffer b_EffectData : register(b0)
{
	float2 ScreenSize;
	float2 Direction;
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
	float redOffset   =  0.009;
	float greenOffset =  0.006;
	float blueOffset  = -0.006;

	float2 textureSize = ScreenSize;

	float2 texCoord = input.Position.xy / textureSize;

	float2 direction = texCoord - Direction;
	
	float4 color = t_Frame.Sample(s_FrameSampler, input.TexCoord);

	color.r = t_Frame.Sample(s_FrameSampler, input.TexCoord + (direction * float2(redOffset, redOffset))).r;
	color.g = t_Frame.Sample(s_FrameSampler, input.TexCoord + (direction * float2(blueOffset , greenOffset))).g;
	color.b = t_Frame.Sample(s_FrameSampler, input.TexCoord + (direction * float2(blueOffset , blueOffset ))).b;

	return color;
}
