#pragma once

#include "Engine/Core/Core.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/PixelShader.h"

namespace Engine
{
	class PostProcessEffect
	{
	public:
		explicit PostProcessEffect(const String& effectName);

		virtual ~PostProcessEffect();

		[[nodiscard]]
		PixelShader& GetEffectShader() const { return *m_EffectPixelShader; }

		virtual void UpdateEffectData(void* updatedEffectData) const = 0;

		virtual void UploadEffectData() const = 0;

		PostProcessEffect(const PostProcessEffect&) = delete;

		PostProcessEffect& operator=(const PostProcessEffect& v) = delete;

		PostProcessEffect(PostProcessEffect&&) noexcept = delete;

		PostProcessEffect& operator=(PostProcessEffect&&) noexcept = delete;

	private:
		SharedPtr<PixelShader> m_EffectPixelShader;

	protected:
		UniquePtr<ConstantBuffer> m_ConstantBuffer;
	};
}
