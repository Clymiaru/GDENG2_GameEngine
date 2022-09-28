#include "Engine/Graphics/Core/SwapChain.h"
#include "Engine/Graphics/Core/GraphicsEngine.h"

Engine::SwapChain::SwapChain() :
	m_DxgiSwapChain{nullptr},
	m_RenderTargetView{nullptr},
	m_DepthStencilView{nullptr}
{
}

auto Engine::SwapChain::Init(HWND windowHandle,
                             const Vector2Int& windowSize) -> bool
{
	auto* device = GraphicsEngine::GetInstance().m_D3DDevice;

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

	auto result = GraphicsEngine::GetInstance().m_DxgiFactory->CreateSwapChain(device, &desc, &m_DxgiSwapChain);
	if (FAILED(result))
	{
		return false;
	}
	ID3D11Texture2D* buffer = nullptr;
	result                  = m_DxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(result))
	{
		return false;
	}
	result = device->CreateRenderTargetView(buffer, nullptr, &m_RenderTargetView);
	buffer->Release();
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

auto Engine::SwapChain::Present(bool vsync) const -> void
{
	m_DxgiSwapChain->Present(vsync, NULL);
}

auto Engine::SwapChain::Release() const -> void
{
	m_DxgiSwapChain->Release();
}
