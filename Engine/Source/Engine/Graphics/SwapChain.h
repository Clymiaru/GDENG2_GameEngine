#pragma once
#include <d3d11.h>

namespace Engine
{
	class Window;
	class SwapChain final
	{
	public:
		SwapChain(Window& window,
		          ID3D11Device* device,
		          IDXGIFactory* factory);

		~SwapChain();

		void Release() const;

		void Present(bool vsync) const;

		[[nodiscard]]
		ID3D11RenderTargetView& GetRenderTargetView() const;

		ID3D11DepthStencilView& GetDepthStencilView() const;

	private:
		void CreateSwapChain(Window& window,
		                     ID3D11Device* device,
		                     IDXGIFactory* factory);

		void CreateRenderTargetView(ID3D11Device* device);

		void CreateDepthStencilView(ID3D11Device* device);

		IDXGISwapChain* m_SwapChain;

		ID3D11RenderTargetView* m_RenderTargetView;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
