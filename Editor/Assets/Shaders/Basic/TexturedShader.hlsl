Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

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

cbuffer Constant : register(b0)
{
	float4x4 Model;
	float4x4 ViewProjection;
	float4 AlbedoColor;
};

VSOutput VSMain(const VSInput input)
{
	VSOutput output;
	
	output.Position = input.Position;
	output.Position = mul(output.Position, Model);
	output.Position = mul(output.Position, ViewProjection);

	output.TexCoord = input.TexCoord;
	
	return output;
}

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	return t_Frame.Sample(s_FrameSampler, input.TexCoord);
}