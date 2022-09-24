#pragma once
#include <d3d11.h>
#include "Engine/Utils/Math.h"

namespace Engine
{
	class DeviceContext;

	class SwapChain
	{
	public:
		SwapChain();

		~SwapChain() = default;

		auto Init(HWND windowHandle,
		          const Vector2Int& windowSize) -> bool;

		auto Present(bool vsync) const -> void;

		auto Release() const -> void;

	private:
		IDXGISwapChain* m_DxgiSwapChain;

		ID3D11RenderTargetView* m_RenderTargetView;

		ID3D11DepthStencilView* m_DepthStencilView;

		friend class DeviceContext;
	};
}
