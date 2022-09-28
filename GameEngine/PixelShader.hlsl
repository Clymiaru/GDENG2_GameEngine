struct PS_INPUT
{
	float4 position: SV_POSITION;
	float4 color: COLOR;
	float4 color1: COLOR1;
};

cbuffer Constant: register(b0)
{
	float Angle;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return lerp(input.color, input.color1, (sin(Angle) + 1.0f) / 2.0f);
}