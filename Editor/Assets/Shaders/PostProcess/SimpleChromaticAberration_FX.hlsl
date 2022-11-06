cbuffer b_EffectData : register(b0)
{
	float4 RGBOffset;
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
	float redOffset   = RGBOffset.x;
	float greenOffset =  RGBOffset.y;
	float blueOffset  = RGBOffset.z;

	float2 texCoord = input.Position.xy / ScreenSize;

	float2 direction = texCoord - Direction;
	
	float4 color = t_Frame.Sample(s_FrameSampler, input.TexCoord);

	float2 dirRedOffset = input.TexCoord + (direction * float2(redOffset, redOffset));
	float2 dirBlueOffset = input.TexCoord + (direction * float2(blueOffset, greenOffset));
	float2 dirGreenOffset = input.TexCoord + (direction * float2(blueOffset, blueOffset));
		
	color.r = t_Frame.Sample(s_FrameSampler, dirRedOffset).r;
	color.g = t_Frame.Sample(s_FrameSampler, dirBlueOffset).g;
	color.b = t_Frame.Sample(s_FrameSampler, dirGreenOffset).b;

	return color;
}
