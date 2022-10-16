#include "pch.h"
#include "SwapChain.h"

#include "Engine/Core/Debug.h"

#include "Engine/Core/Window.h"

namespace Engine
{
	SwapChain::SwapChain(Window& window,
	                     ID3D11Device* device,
	                     IDXGIFactory* factory) :
		m_SwapChain{nullptr},
		m_RenderTargetView{nullptr},
		m_DepthStencilView{nullptr}
	{
		CreateSwapChain(window,
		                device,
		                factory);

		CreateRenderTargetView(device);
	}

	SwapChain::~SwapChain() = default;

	void SwapChain::Release() const
	{
		if (m_SwapChain != nullptr)
			m_SwapChain->Release();

		if (m_RenderTargetView != nullptr)
			m_RenderTargetView->Release();

		if (m_DepthStencilView != nullptr)
			m_DepthStencilView->Release();
	}

	void SwapChain::Present(bool vsync) const
	{
		m_SwapChain->Present(vsync, NULL);
	}

	ID3D11RenderTargetView& SwapChain::GetRenderTargetView() const
	{
		return *m_RenderTargetView;
	}

	void SwapChain::CreateSwapChain(Window& window,
	                                ID3D11Device* device,
	                                IDXGIFactory* factory)
	{
		const Vector2 windowSize = window.GetSize();
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount       = 1;
		desc.BufferDesc.Width  = static_cast<Uint>(windowSize.X());
		desc.BufferDesc.Height = static_cast<Uint>(windowSize.Y());

		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow                       = window.GetHandle();
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.Windowed                           = TRUE;

		auto result = factory->CreateSwapChain(device,
		                                       &desc,
		                                       &m_SwapChain);

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create swap chain!")
	}

	void SwapChain::CreateRenderTargetView(ID3D11Device* device)
	{
		ID3D11Texture2D* buffer = nullptr;

		HRESULT result = m_SwapChain->GetBuffer(0,
		                                        __uuidof(ID3D11Texture2D),
		                                        reinterpret_cast<void**>(&buffer));

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to get buffer!")

		result = device->CreateRenderTargetView(buffer,
		                                        nullptr,
		                                        &m_RenderTargetView);
		buffer->Release();
		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create RenderTargetView!")
	}

	// TODO:
	void SwapChain::CreateDepthStencilView(ID3D11Device* device)
	{
		ID3D11Texture2D* buffer = nullptr;

		D3D11_TEXTURE2D_DESC textureDesc = {};

		HRESULT result = m_SwapChain->GetBuffer(0,
												__uuidof(ID3D11Texture2D),
												reinterpret_cast<void**>(&buffer));

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to get buffer!")

		result = device->CreateRenderTargetView(buffer,
												nullptr,
												&m_RenderTargetView);
		buffer->Release();
		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create RenderTargetView!")
	}
}
