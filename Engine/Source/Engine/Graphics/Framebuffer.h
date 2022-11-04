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

		ID3D11Texture2D* ExistingTexture = nullptr;

		bool SwapChainTarget = false;
	};

	class Framebuffer final
	{
	public:
		explicit Framebuffer(const FramebufferProfile& profile);

		~Framebuffer();

		[[nodiscard]]
		ID3D11ShaderResourceView& GetFrame() const
		{
			return m_RenderTarget->GetShaderResourceView();
		}

		[[nodiscard]]
		ID3D11RenderTargetView& GetRenderTarget() const
		{
			return m_RenderTarget->GetRenderTargetView();
		}

		[[nodiscard]]
		ID3D11DepthStencilView& GetDepthStencil() const
		{
			return *m_DepthStencilView;
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
