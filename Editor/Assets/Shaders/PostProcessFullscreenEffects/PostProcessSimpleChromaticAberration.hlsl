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

cbuffer Constant: register(b0)
{
	float2 ScreenSize;
	float2 Direction;
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
	float redOffset   =  0.009;
	float greenOffset =  0.006;
	float blueOffset  = -0.006;

	float2 direction = float2(Direction.x, Direction.y);
	
	float2 textureSize = float2(1280, 1080);
	
	float2 texCoord2 = input.position.xy / textureSize;
	
	float4 color = tex.Sample(splr, input.texCoord);

	color.r = tex.Sample(splr, input.texCoord + (direction * float2(redOffset, redOffset))).r;
	color.g = tex.Sample(splr, input.texCoord + (direction * float2(blueOffset , greenOffset))).g;
	color.b = tex.Sample(splr, input.texCoord + (direction * float2(blueOffset , blueOffset ))).b;

	return color;
}