#pragma once
#include "PostProcessEffect.h"

namespace Engine
{
	class VignettePostProcessEffect final : public PostProcessEffect
	{
	public:
		explicit VignettePostProcessEffect();

		~VignettePostProcessEffect() override;

		void UploadEffectData() const override;

		void UpdateEffectData(void* updatedEffectData) const override;
	};	
}

