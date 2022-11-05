#include "pch.h"
#include "VignettePostProcessEffect.h"

namespace Engine
{
	VignettePostProcessEffect::VignettePostProcessEffect() :
		PostProcessEffect{"VignetteEffect"}
	{
	}

	VignettePostProcessEffect::~VignettePostProcessEffect() = default;

	void VignettePostProcessEffect::UploadEffectData() const
	{
	}

	void VignettePostProcessEffect::UpdateEffectData(void* updatedEffectData) const
	{
	}
}
