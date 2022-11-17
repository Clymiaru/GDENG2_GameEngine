#pragma once
#include <d3d11.h>

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class RenderTexture final
	{
	public:

		explicit RenderTexture(ID3D11Device& deviceRef,
							   uint32_t width,
							   uint32_t height);

		explicit RenderTexture(ID3D11Device& deviceRef,
							   ID3D11Texture2D* existingTexture,
							   bool isSwapChainTexture = false);

		~RenderTexture();
		
		[[nodiscard]]
		ID3D11ShaderResourceView& GetShaderResourceView() const
		{
			return *m_View;
		}

		[[nodiscard]]
		ID3D11RenderTargetView& GetRenderTargetView() const
		{
			return *m_RenderTarget;
		}

		RenderTexture(const RenderTexture&)                = delete;
		RenderTexture& operator=(const RenderTexture&)     = delete;
		RenderTexture(RenderTexture&&) noexcept            = delete;
		RenderTexture& operator=(RenderTexture&&) noexcept = delete;

	private:
		

		ID3D11RenderTargetView* m_RenderTarget;

		ID3D11ShaderResourceView* m_View;

		friend class RenderDevice;
		friend class RenderContext;
	};
}
