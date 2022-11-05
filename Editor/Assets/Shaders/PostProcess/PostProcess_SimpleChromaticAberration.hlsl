cbuffer Constant: register(b0)
{
	float2 ScreenSize;
	float2 Direction;
};

Texture2D tex;

SamplerState splr;

struct PSInput
{
	float4 Position: SV_POSITION;
	float2 TexCoord : TexCoord;
};

float4 PSMain(PSInput input) : SV_TARGET
{
	float redOffset   =  0.009;
	float greenOffset =  0.006;
	float blueOffset  = -0.006;

	float2 direction = Direction;
	
	float2 textureSize = ScreenSize;
	
	float2 texCoord2 = input.Position.xy / textureSize;
	
	float4 color = tex.Sample(splr, input.TexCoord);

	color.r = tex.Sample(splr, input.TexCoord + (direction * float2(redOffset, redOffset))).r;
	color.g = tex.Sample(splr, input.TexCoord + (direction * float2(blueOffset , greenOffset))).g;
	color.b = tex.Sample(splr, input.TexCoord + (direction * float2(blueOffset , blueOffset ))).b;

	return color;
}
