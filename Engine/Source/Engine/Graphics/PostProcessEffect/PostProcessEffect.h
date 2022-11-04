#pragma once
#include "Engine/Core/Core.h"
#include "Engine/ECS/Component/RenderComponent.h"

namespace Engine
{
	class ConstantBuffer;

	class PixelShader;

	class PostProcessEffect
	{
	public:
		explicit PostProcessEffect(const String& effectName);

		~PostProcessEffect();

		PixelShader& GetEffectShader() const { return *m_EffectPixelShader; }

		void UploadData();

		PostProcessEffect(const PostProcessEffect&) = delete;

		PostProcessEffect& operator=(const PostProcessEffect& v) = delete;

		PostProcessEffect(PostProcessEffect&&) noexcept = delete;

		PostProcessEffect& operator=(PostProcessEffect&&) noexcept = delete;

	private:
		SharedPtr<PixelShader> m_EffectPixelShader;
		UniquePtr<ConstantBuffer> m_ConstantBuffer;

		ID3D11RenderTargetView* m_PostProcessRenderTarget;
	};
}
