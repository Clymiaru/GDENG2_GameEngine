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
	float3 colors[7] =
	{
		float3(1.0f, 0.0f, 0.0f),
		float3(1.0f, 0.5f, 0.0f),
		float3(1.0f, 1.0f, 0.0f),
		float3(0.0f, 1.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(0.18f, 0.17f, 0.37f),
		float3(0.55f, 0.0f, 1.0f)
	};

	float2 uv = input.TexCoord;
	uv *= 7;

	float colorAIndex = floor(uv.x) % 7;
	float colorBIndex = (colorAIndex + 1) % 7;
	float3 rainbowColor = lerp(colors[colorAIndex], colors[colorBIndex], 0.5f);
	
	return float4(rainbowColor.x, rainbowColor.y, rainbowColor.z, 1.0f);
}