#include "pch.h"

#include "Engine/Graphics/SwapChain.h"

#include "Engine/Utils/Debug.h"

namespace Engine
{
	SwapChain::SwapChain() :
		m_SwapChain{nullptr},
		m_RenderTargetView{nullptr},
		m_DepthStencilView{nullptr}
	{
	}

	void SwapChain::Initialize(HWND windowHandle,
	                           const Vector2Int& windowSize,
	                           ID3D11Device* device,
	                           IDXGIFactory* factory)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount       = 1;
		desc.BufferDesc.Width  = windowSize.X;
		desc.BufferDesc.Height = windowSize.Y;

		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow                       = windowHandle;
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.Windowed                           = TRUE;

		auto result = factory->CreateSwapChain(device,
		                                       &desc,
		                                       &m_SwapChain);

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create swap chain!")

		ID3D11Texture2D* buffer = nullptr;

		result = m_SwapChain->GetBuffer(0,
		                                __uuidof(ID3D11Texture2D),
		                                reinterpret_cast<void**>(&buffer));

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to get buffer!")

		result = device->CreateRenderTargetView(buffer,
		                                        nullptr,
		                                        &m_RenderTargetView);
		buffer->Release();

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create RenderTargetView!")
	}

	void SwapChain::Present(bool vsync) const
	{
		m_SwapChain->Present(vsync, NULL);
	}

	ID3D11RenderTargetView& SwapChain::GetRenderTargetView() const
	{
		return *m_RenderTargetView;
	}

	void SwapChain::Terminate() const
	{
		m_SwapChain->Release();
	}
}