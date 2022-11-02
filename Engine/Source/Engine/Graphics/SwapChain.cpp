#include "pch.h"
#include "SwapChain.h"

#include "DeviceContext.h"

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

	void SwapChain::Present(const uint32_t vsync) const
	{
		m_SwapChain->Present(vsync, DXGI_SWAP_EFFECT_FLIP_DISCARD);
	}

	ID3D11RenderTargetView& SwapChain::GetRenderTargetView() const
	{
		return *m_RenderTargetView;
	}

	ID3D11DepthStencilView& SwapChain::GetDepthStencilView() const
	{
		return *m_DepthStencilView;
	}

	void SwapChain::CreateSwapChain(Window& window,
	                                ID3D11Device* device,
	                                IDXGIFactory* factory)
	{
		const Rect<uint32_t> windowRect = window.WindowRect();
		const Vector2Uint windowSize    = Vector2Uint(windowRect.Width, windowRect.Height);

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferDesc.Width                   = windowSize.x;
		desc.BufferDesc.Height                  = windowSize.y;
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
		desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_CENTERED;

		desc.SampleDesc.Count   = 1;
		desc.SampleDesc.Quality = 0;

		desc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		desc.BufferCount        = 1;
		desc.OutputWindow       = window.GetHandle();

		desc.Windowed           = TRUE;

		const auto result = factory->CreateSwapChain(device,
		                                             &desc,
		                                             &m_SwapChain);

		Debug::Assert(SUCCEEDED(result), "Failed to create swap chain!");
	}

	void SwapChain::CreateRenderTargetView(ID3D11Device* device)
	{
		ID3D11Texture2D* buffer = nullptr;

		HRESULT result = m_SwapChain->GetBuffer(0,
		                                        __uuidof(ID3D11Texture2D),
		                                        reinterpret_cast<void**>(&buffer));

		Debug::Assert(SUCCEEDED(result), "Failed to get buffer!");

		result = device->CreateRenderTargetView(buffer,
		                                        nullptr,
		                                        &m_RenderTargetView);
		buffer->Release();
		Debug::Assert(SUCCEEDED(result), "Failed to create RenderTargetView!");

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width                = 1280;
		textureDesc.Height               = 720;
		textureDesc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
		textureDesc.Usage                = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags            = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.MipLevels            = 1;
		textureDesc.SampleDesc.Count     = 1;
		textureDesc.SampleDesc.Quality   = 0;
		textureDesc.MiscFlags            = 0;
		textureDesc.ArraySize            = 1;
		textureDesc.CPUAccessFlags       = 0;

		device->CreateTexture2D(&textureDesc, NULL, &buffer);
		device->CreateDepthStencilView(buffer, NULL, &m_DepthStencilView);
		buffer->Release();
	}

	// TODO:
	void SwapChain::CreateDepthStencilView(ID3D11Device* device)
	{
	}
}
