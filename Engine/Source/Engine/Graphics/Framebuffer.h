#pragma once
#include <d3d11.h>

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

		ID3D11ShaderResourceView& GetShaderResourceView() const;

		ID3D11RenderTargetView& GetRenderTargetView() const;

		ID3D11DepthStencilView& GetDepthStencilView() const;

		void ClearRenderTarget(const Color& clearColor) const;

		void ClearDepthStencil() const;

	private:
		FramebufferProfile m_Profile;

		ID3D11Texture2D* m_FrameTexture;

		ID3D11ShaderResourceView* m_ShaderResourceView;

		ID3D11RenderTargetView* m_RenderTargetView;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
