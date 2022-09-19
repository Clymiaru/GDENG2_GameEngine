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
		~SwapChain();
		bool Init(HWND windowHandle, const Engine::Vector2Int& windowSize);
		bool Present(bool vsync);
		bool Release();
		
	private:
		IDXGISwapChain* m_DXGISwapChain;
		ID3D11RenderTargetView* m_RenderTargetView;

		void CreateRenderTargetView(ID3D11Resource* resource, ID3D11RenderTargetView** renderTargetView);

		friend class DeviceContext;
	};
}