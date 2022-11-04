#pragma once
#include <d3d11.h>

#include "Engine/Math/Vector2.h"

namespace Engine
{
	class DeviceContext;

	class Window;

	class SwapChain final
	{
	public:
		SwapChain(Window& window,
		          ID3D11Device* device,
		          IDXGIFactory* factory);

		~SwapChain();

		void Release() const;

		void Present(uint32_t vsync) const;

		ID3D11RenderTargetView& GetBackbufferRenderTarget() const;

		ID3D11DepthStencilView& GetDepthStencil() const;

		void ResizeBuffers(Vector2Uint& size,
		                   DeviceContext& deviceContext,
		                   ID3D11Device* device);

		SwapChain(const SwapChain&) = delete;

		SwapChain& operator=(const SwapChain&) = delete;

		SwapChain(SwapChain&&) noexcept = delete;

		SwapChain& operator=(SwapChain&&) noexcept = delete;

	private:
		void CreateSwapChain(ID3D11Device* device,
		                     IDXGIFactory* factory);

		ID3D11Texture2D* GetBackBuffer() const;

		IDXGISwapChain* m_SwapChain;

		ID3D11RenderTargetView* m_BackbufferRenderTarget;

		ID3D11DepthStencilView* m_DepthStencil;

		Window& m_WindowRef;
	};
}
