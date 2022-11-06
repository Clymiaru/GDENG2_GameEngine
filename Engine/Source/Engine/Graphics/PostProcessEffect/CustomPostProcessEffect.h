#pragma once
#include "PostProcessEffect.h"

namespace Engine
{
	class CustomPostProcessEffect : public PostProcessEffect
	{
	public:
		explicit CustomPostProcessEffect();

		~CustomPostProcessEffect() override;

		void UploadEffectData() const override;

		void UpdateEffectData(void* updatedEffectData) const override;
	};
}
