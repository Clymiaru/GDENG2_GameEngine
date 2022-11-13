#pragma once
#include <d3d11.h>
#include "RenderTexture.h"

namespace Engine
{
	struct FramebufferProfile
	{
		unsigned int Width = 0;

		unsigned int Height = 0;

		ID3D11Texture2D* ExistingTexture = nullptr;

		bool SwapChainTarget = false;
	};

	class Framebuffer final
	{
	public:
		explicit Framebuffer(const FramebufferProfile& profile,
		                     ID3D11Device& device);

		~Framebuffer();

		[[nodiscard]]
		const FramebufferProfile& GetInfo() const
		{
			return m_Profile;
		}

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

		UniquePtr<RenderTexture> m_RenderTarget;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
