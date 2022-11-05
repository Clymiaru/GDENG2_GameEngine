#include "pch.h"
#include "SimpleChromaticAberrationPostProcessEffect.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Renderer.h"




namespace Engine
{
	SimpleChromaticAberrationPostProcessEffect::SimpleChromaticAberrationPostProcessEffect(SimpleChromaticAberrationEffectData effectData) :
		PostProcessEffect{"SimpleChromaticAberration"}
	{
		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>((void*)&effectData, sizeof(SimpleChromaticAberrationEffectData));
	}

	SimpleChromaticAberrationPostProcessEffect::~SimpleChromaticAberrationPostProcessEffect()
	{
	}

	void SimpleChromaticAberrationPostProcessEffect::UploadEffectData() const
	{
		Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);
	}

	void SimpleChromaticAberrationPostProcessEffect::UpdateEffectData(void* updatedEffectData) const
	{
		// Data check?
		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, updatedEffectData);
	}
}
