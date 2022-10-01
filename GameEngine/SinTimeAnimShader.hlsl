struct VS_INPUT
{
	float4 position: POSITION;
	float4 size: SIZE;
	float4 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float4 size: SIZE;
	float4 color: COLOR;
};

cbuffer Constant: register(b0)
{
	float Time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	output.position = input.position;
	output.color = input.color;
	output.size = input.size;
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

	if (input.size.x - input.position.x > 0.0f && input.size.x - input.position.x < 0.4f)
	{
		resultColor = smoothstep(input.color, colorA, (sin(Time) + 1.0f) / 2.0f);
	}
	else
	{
		resultColor = smoothstep(input.color, colorB, (sin(Time) + 1.0f) / 2.0f);
	}
	
	return resultColor;
}