Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

struct VSInput
{
	float4 Position : Position;
	float2 UV : UV;
	float4 Normal : Normal;
};

struct VSOutput
{
	float4 Position : SV_Position;
	float2 UV : UV;
	float4 Normal : Normal;
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

	output.UV = input.UV;
	output.Normal = input.Normal;
	
	return output;
}

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 UV : UV;
	float4 Normal : Normal;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	return t_Frame.Sample(s_FrameSampler, input.UV) * AlbedoColor;
}