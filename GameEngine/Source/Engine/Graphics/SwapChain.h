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

		auto Initialize(HWND windowHandle,
		                const Vector2Int& windowSize,
		                ID3D11Device* device,
		                IDXGIFactory* factory) -> bool;

		auto Terminate() const -> void;

		auto Present(bool vsync) const -> void;

		[[nodiscard]]
		auto GetRenderTargetView() const -> ID3D11RenderTargetView&;

	private:
		IDXGISwapChain* m_SwapChain;

		ID3D11RenderTargetView* m_RenderTargetView;

		ID3D11DepthStencilView* m_DepthStencilView;
	};
}
