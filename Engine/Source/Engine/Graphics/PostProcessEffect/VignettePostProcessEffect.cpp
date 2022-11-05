#include "pch.h"
#include "VignettePostProcessEffect.h"

#include "Engine/Graphics/Renderer.h"

namespace Engine
{
	VignettePostProcessEffect::VignettePostProcessEffect(VignetteEffectData effectData) :
		PostProcessEffect{"VignetteEffect"}
	{
		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>((void*)&effectData, sizeof(VignetteEffectData));
	}

	VignettePostProcessEffect::~VignettePostProcessEffect() = default;

	void VignettePostProcessEffect::UploadEffectData() const
	{
		Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);
	}

	void VignettePostProcessEffect::UpdateEffectData(void* updatedEffectData) const
	{
		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, updatedEffectData);
	}
}
