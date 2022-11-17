#pragma once
#include <d3d11.h>

namespace Engine
{
	class Framebuffer;

	class RenderContext;

	class Window;

	class SwapChain final
	{
	public:
		SwapChain(Window& window,
		          ID3D11Device* device,
		          IDXGIFactory* factory);

		~SwapChain();

		// TODO: Determine if the resource will be released on command or through RAII
		void Release() const;

		void Present(uint32_t vsync) const;

		[[nodiscard]]
		Framebuffer& GetBackbuffer() const;

		void Resize(unsigned int width, unsigned int height,
		            RenderContext& deviceContext, ID3D11Device* device);

		SwapChain(const SwapChain&) = delete;

		SwapChain& operator=(const SwapChain&) = delete;

		SwapChain(SwapChain&&) noexcept = delete;

		SwapChain& operator=(SwapChain&&) noexcept = delete;

	private:
		void CreateSwapChain(ID3D11Device* device,
		                     IDXGIFactory* factory);

		ID3D11Texture2D* GetBackBuffer() const;

		IDXGISwapChain* m_SwapChain;

		Framebuffer* m_MainFramebuffer;

		Window& m_WindowRef;
	};
}
