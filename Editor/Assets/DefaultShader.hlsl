struct VS_INPUT
{
	float4 position: POSITION;
	float4 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float4 color: COLOR;
};

cbuffer Constant: register(b0)
{
	float4x4 Model;
	float4x4 ViewProjection;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position;
	
	output.position = mul(output.position, Model);
	output.position = mul(output.position, ViewProjection);
	
	output.color = input.color;
	return output;
}

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 color: COLOR;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(input.color.x, input.color.y, input.color.z, 1.0f);
}