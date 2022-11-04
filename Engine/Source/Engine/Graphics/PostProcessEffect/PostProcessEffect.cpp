#include "pch.h"
#include "PostProcessEffect.h"

#include "Engine/Graphics/ShaderLibrary.h"

#include "Engine/Math/Vector2.h"

__declspec(align(16))
struct Constant
{
	Engine::Vector2Float ScreenSize;
	Engine::Vector2Float Direction;
};

namespace Engine
{
	PostProcessEffect::PostProcessEffect(const String& effectName)
	{
		const String shaderEffectName = "PostProcess_" + effectName;
		String shaderEffectShaderPath = "Assets/Shaders/PostProcess/";
		shaderEffectShaderPath += shaderEffectName;
		shaderEffectShaderPath += ".hlsl";
		ShaderLibrary::Register<PixelShader>(shaderEffectShaderPath,
		                                     "PSMain");

		m_EffectPixelShader = ShaderLibrary::GetShaderRef<PixelShader>(shaderEffectName);

		Constant* constant = new Constant{};

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant, sizeof(Constant));
	}

	PostProcessEffect::~PostProcessEffect() = default;
}
