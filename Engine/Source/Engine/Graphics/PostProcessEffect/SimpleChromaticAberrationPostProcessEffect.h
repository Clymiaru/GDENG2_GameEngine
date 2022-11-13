#pragma once
#include "PostProcessEffect.h"

#include "Engine/Math/Math.h"
namespace Engine
{
	__declspec(align(16))
	struct SimpleChromaticAberrationEffectData
	{
		Color RGBOffset;
		
		Vector2Float ScreenSize;

		Vector2Float Direction;
	};
	
	class SimpleChromaticAberrationPostProcessEffect : public PostProcessEffect
	{
	public:
		explicit SimpleChromaticAberrationPostProcessEffect(SimpleChromaticAberrationEffectData effectData);

		~SimpleChromaticAberrationPostProcessEffect() override;

		void UploadEffectData() const override;

		void UpdateEffectData(void* updatedEffectData) const override;
	};
}
