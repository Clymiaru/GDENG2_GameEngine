Texture2D t_Frame : register(t0);

SamplerState s_FrameSampler : register(s0);

struct PSInput
{
	float4 Position: SV_Position;
	float2 TexCoord : TexCoord;
};

float4 circle(float2 position, float radius)
{
	float2 l = position - float2(0.5f, 0.5f);

	float result = 1.0f - smoothstep(radius - (radius * 0.01),
						 radius + (radius * 0.01),
						 dot(l,l) * 4.0);
	
	float4 color = float4(result, result, result, 1.0);
	
	return color;
}

float4 PSMain(const PSInput input) : SV_TARGET
{
	float2 uv = input.TexCoord;

	uv *= 2.0;
	uv = frac(uv);

	float4 color = circle(uv, 0.75f);

	if (uv.y >= 0.0f && uv.y < 0.25f)
	{
		color *= t_Frame.Sample(s_FrameSampler, input.TexCoord + float2(0.1f, 0.0f));
	}
	else if (uv.y >= 0.75f && uv.y < 1.0f)
	{
		color *= t_Frame.Sample(s_FrameSampler, input.TexCoord - float2(0.1f, 0.0f));
	}
	else
	{
		color *= t_Frame.Sample(s_FrameSampler, input.TexCoord);
	}
	
	return color;
}

