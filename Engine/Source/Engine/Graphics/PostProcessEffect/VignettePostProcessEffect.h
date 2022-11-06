#pragma once
#include "PostProcessEffect.h"

namespace Engine
{
	struct VignetteEffectData
	{
		Color EffectColor;
		Vector2Float EffectPosition;
		Vector2Float ScreenSize;
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

