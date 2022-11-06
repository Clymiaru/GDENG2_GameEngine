#pragma once
#include "PostProcessEffect.h"

namespace Engine
{
	__declspec(align(16))
	struct VignetteEffectData
	{
		Color EffectColor;
		Vector2Float EffectPosition;
		Vector2Float IntensitySmoothness;
	};
	
	class VignettePostProcessEffect final : public PostProcessEffect
	{
	public:
		explicit VignettePostProcessEffect(VignetteEffectData effectData);

		~VignettePostProcessEffect() override;

		void UploadEffectData() const override;

		void UpdateEffectData(void* updatedEffectData) const override;
	};	
}

