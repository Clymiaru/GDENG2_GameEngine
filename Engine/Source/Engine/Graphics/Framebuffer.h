#pragma once
#include <d3d11.h>

#include "RenderTexture.h"

namespace Engine
{
	struct Color;

	struct FramebufferProfile
	{
		uint32_t Width;

		uint32_t Height;

		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer final
	{
	public:
		explicit Framebuffer(const FramebufferProfile& profile);

		~Framebuffer();

		void Clear(const Color& clearColor) const;

		void SetAsRenderTarget();

		ID3D11ShaderResourceView& GetFrame() const
		{
			return m_RenderTarget->GetShaderResourceView();
		}

		Framebuffer(const Framebuffer&) = delete;
	
		Framebuffer& operator=(const Framebuffer&) = delete;
	
		Framebuffer(Framebuffer&&) noexcept = delete;
	
		Framebuffer& operator=(Framebuffer&&) noexcept = delete;

	private:
		FramebufferProfile m_Profile;

		RenderTexture* m_RenderTarget;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
