#pragma once
#include <d3d11.h>
#include "Engine/Utils/Math.h"

namespace Engine
{
	class DeviceContext;

	class SwapChain final
	{
	public:
		SwapChain();

		~SwapChain() = default;

		void Initialize(HWND windowHandle,
		                const Vector2Int& windowSize,
		                ID3D11Device* device,
		                IDXGIFactory* factory);

		void Terminate() const;

		void Present(bool vsync) const;

		[[nodiscard]]
		ID3D11RenderTargetView& GetRenderTargetView() const;

	private:
		IDXGISwapChain* m_SwapChain;

		ID3D11RenderTargetView* m_RenderTargetView;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
