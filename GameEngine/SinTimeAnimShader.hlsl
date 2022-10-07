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
	float4x4 View;
	float4x4 Projection;
	float4x4 Model;
	float Time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.position = mul(input.position, Model);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);
	
	output.color = input.color;
	return output;
}

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 size: SIZE;
	float4 color: COLOR;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float4 colorA = float4(0.1f, 0.1f, 0.1f, 0.9f);
	float4 colorB = float4(0.9f, 0.9f, 0.9f, 0.9f);
	float4 resultColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	resultColor = smoothstep(input.color, colorA, (sin(Time) + 1.0f) / 2.0f);
	return resultColor;
}