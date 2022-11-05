Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

struct PSInput
{
	float4 Position: SV_Position;
	float2 TexCoord : TexCoord;
};

float4 PSMain(PSInput input) : SV_Target
{
	return t_Frame.Sample(s_FrameSampler, input.TexCoord);
}