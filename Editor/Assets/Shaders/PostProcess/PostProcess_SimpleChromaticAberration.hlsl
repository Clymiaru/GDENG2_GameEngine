struct VSInput
{
	float4 Position: POSITION;
	float2 TexCoord : TEXCOORD;
	float4 Color: COLOR;
};

struct VSOutput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
	float4 Color: COLOR;
};

cbuffer Constant: register(b0)
{
	float2 ScreenSize;
	float2 Direction;
};

VSOutput VSMain(VSInput input)
{
	VSOutput output;
	output.Position = input.Position;
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	return output;
}

Texture2D tex;

SamplerState splr;

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
	float4 Color: COLOR;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	float redOffset   =  0.009;
	float greenOffset =  0.006;
	float blueOffset  = -0.006;

	float2 direction = float2(Direction.x, Direction.y);
	
	float2 textureSize = float2(1280, 1080);
	
	float2 texCoord2 = input.Position.xy / textureSize;
	
	float4 color = tex.Sample(splr, input.TexCoord);

	color.r = tex.Sample(splr, input.TexCoord + (direction * float2(redOffset, redOffset))).r;
	color.g = tex.Sample(splr, input.TexCoord + (direction * float2(blueOffset , greenOffset))).g;
	color.b = tex.Sample(splr, input.TexCoord + (direction * float2(blueOffset , blueOffset ))).b;

	return color;
}