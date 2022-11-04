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
		m_WindowRef{window}
	{
		CreateSwapChain(device, factory);

		const auto backBuffer = GetBackBuffer();

		HRESULT result = device->CreateRenderTargetView(backBuffer,
		                                                nullptr,
		                                                &m_BackbufferRenderTarget);
		Debug::Assert(SUCCEEDED(result), "Failed to create RenderTargetView!");

		backBuffer->Release();

		ID3D11Texture2D* depthStencilTexture = nullptr;
		D3D11_TEXTURE2D_DESC textureDesc     = {};
		textureDesc.Width                    = window.WindowRect().Width;
		textureDesc.Height                   = window.WindowRect().Height;
		textureDesc.Format                   = DXGI_FORMAT_D24_UNORM_S8_UINT;
		textureDesc.Usage                    = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags                = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.MipLevels                = 1;
		textureDesc.SampleDesc.Count         = 1;
		textureDesc.SampleDesc.Quality       = 0;
		textureDesc.MiscFlags                = 0;
		textureDesc.ArraySize                = 1;
		textureDesc.CPUAccessFlags           = 0;

		result = device->CreateTexture2D(&textureDesc, nullptr, &depthStencilTexture);
		Debug::Assert(SUCCEEDED(result), "Failed to create Depth Stencil Texture!");

		result = device->CreateDepthStencilView(depthStencilTexture, nullptr, &m_DepthStencil);
		Debug::Assert(SUCCEEDED(result), "Failed to create Depth Stencil View!");

		depthStencilTexture->Release();
	}

	SwapChain::~SwapChain() = default;

	void SwapChain::Release() const
	{
		if (m_DepthStencil != nullptr)
			m_DepthStencil->Release();

		if (m_BackbufferRenderTarget != nullptr)
			m_BackbufferRenderTarget->Release();

		if (m_SwapChain != nullptr)
			m_SwapChain->Release();
	}

	ID3D11Texture2D* SwapChain::GetBackBuffer() const
	{
		ID3D11Texture2D* buffer = nullptr;

		HRESULT result = m_SwapChain->GetBuffer(0,
		                                        __uuidof(ID3D11Texture2D),
		                                        reinterpret_cast<void**>(&buffer));

		Debug::Assert(SUCCEEDED(result), "Failed to get buffer!");
		return buffer;
	}

	void SwapChain::CreateSwapChain(ID3D11Device* device,
	                                IDXGIFactory* factory)
	{
		const Rect<uint32_t> windowRect = m_WindowRef.WindowRect();
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

		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		desc.BufferCount  = 1;
		desc.OutputWindow = m_WindowRef.GetHandle();

		desc.Windowed = TRUE;

		const auto result = factory->CreateSwapChain(device,
		                                             &desc,
		                                             &m_SwapChain);

		Debug::Assert(SUCCEEDED(result), "Failed to create swap chain!");
	}

	void SwapChain::Present(const uint32_t vsync) const
	{
		m_SwapChain->Present(vsync, 0);
	}

	ID3D11RenderTargetView& SwapChain::GetBackbufferRenderTarget() const
	{
		return *m_BackbufferRenderTarget;
	}

	ID3D11DepthStencilView& SwapChain::GetDepthStencil() const
	{
		return *m_DepthStencil;
	}

	void SwapChain::ResizeBuffers(Vector2Uint& size,
	                              DeviceContext& deviceContext,
	                              ID3D11Device* device)
	{
		if (deviceContext.m_DeviceContext == nullptr || device == nullptr)
			return;
		
		deviceContext.m_DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

		m_BackbufferRenderTarget->Release();

		HRESULT result = m_SwapChain->ResizeBuffers(1, size.x, size.y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		ID3D11Texture2D* buffer;
		result = m_SwapChain->GetBuffer(0, __uuidof( ID3D11Texture2D),
		                                (void**)&buffer);
		// Perform error handling here!

		result = device->CreateRenderTargetView(buffer, nullptr,
		                                              &m_BackbufferRenderTarget);
		// Perform error handling here!
		buffer->Release();

		deviceContext.m_DeviceContext->OMSetRenderTargets(1, &m_BackbufferRenderTarget, m_DepthStencil);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = size.x;
		vp.Height = size.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		deviceContext.m_DeviceContext->RSSetViewports( 1, &vp );
	}
}
