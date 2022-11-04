struct VS_INPUT
{
	float4 position: POSITION;
	float2 texCoord : TEXCOORD;
	float4 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float2 texCoord : TexCoord;
	float4 color: COLOR;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position;
	output.texCoord = input.texCoord;
	output.color = input.color;
	return output;
}

Texture2D tex;

SamplerState splr;

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texCoord : TexCoord;
	float4 color: COLOR;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float2 uv = input.texCoord;
	uv *= 1.0f - uv.yx;
	float vig = uv.x * uv.y * 15.0f;
	vig = pow(vig, 0.75f);
	
	float4 color = tex.Sample(splr, input.texCoord);
	return color * input.color * vig;
}