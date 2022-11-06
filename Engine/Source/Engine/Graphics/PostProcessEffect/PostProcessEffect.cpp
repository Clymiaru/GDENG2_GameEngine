#include "pch.h"
#include "PostProcessEffect.h"

#include "Engine/Graphics/ShaderLibrary.h"

#include "Engine/Math/Vector2.h"

__declspec(align(16))
struct SimpleChromaticAberrationConstantData
{
	Engine::Vector2Float ScreenSize;

	Engine::Vector2Float Direction;
};

namespace Engine
{
	PostProcessEffect::PostProcessEffect(const String& effectName) :
		Name{effectName},
		m_EffectPixelShader{nullptr},
		m_ConstantBuffer{nullptr}
	{
		const String shaderEffectName = effectName + "_FX";
		String shaderEffectShaderPath = "Assets/Shaders/PostProcess/";
		shaderEffectShaderPath += shaderEffectName;
		shaderEffectShaderPath += ".hlsl";
		ShaderLibrary::Register<PixelShader>(shaderEffectShaderPath);

		m_EffectPixelShader = ShaderLibrary::GetShaderRef<PixelShader>(shaderEffectName);
	}

	PostProcessEffect::~PostProcessEffect() = default;
}
