struct VS_INPUT
{
	float4 position: POSITION;
	float4 position1: POSITION1;
	float4 color: COLOR;
	float4 color1: COLOR1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float4 color: COLOR;
	float4 color1: COLOR1;
};

cbuffer Constant: register(b0)
{
	float4x4 View;
	float4x4 Projection;
	float4x4 Model;
	float Ratio;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.position = mul(input.position, Model);
	output.position = mul(output.position, View);
	output.position = mul(output.position, Projection);
	
	output.color = input.color;
	output.color1 = input.color1;
	return output;
}

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 color: COLOR;
	float4 color1: COLOR1;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float4 resultColor = lerp(input.color, input.color1, Ratio);
	return resultColor;
}