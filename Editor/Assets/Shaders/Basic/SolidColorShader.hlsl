struct VSInput
{
	float4 Position : Position;
};

struct VSOutput
{
	float4 Position : SV_Position;
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
	
	return output;
}

struct PSInput
{
	float4 Position: SV_POSITION;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	return float4(AlbedoColor.x, AlbedoColor.y, AlbedoColor.z, 1.0f);
}