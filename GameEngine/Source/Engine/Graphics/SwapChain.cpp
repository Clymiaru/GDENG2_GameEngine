#include "SwapChain.h"
#include "GraphicsEngine.h"

Engine::SwapChain::SwapChain()
{
}

Engine::SwapChain::~SwapChain()
{
}

bool Engine::SwapChain::Init(HWND windowHandle, const Engine::Vector2Int& windowSize)
{
	auto* device = GraphicsEngine::GetInstance().m_D3DDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = windowSize.X;
	desc.BufferDesc.Height = windowSize.Y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = windowHandle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	auto result = GraphicsEngine::GetInstance().m_DXGIFactory->CreateSwapChain(device, &desc, &m_DXGISwapChain);

	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* buffer = nullptr;
	result = m_DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(result))
	{
		return false;
	}

	result = device->CreateRenderTargetView(buffer, NULL, &m_RenderTargetView);
	buffer->Release();

	if (FAILED(result))
	{
		return false;
	}

	// Init Swap Chain


	return true;
}

bool Engine::SwapChain::Present(bool vsync)
{
	m_DXGISwapChain->Present(vsync, NULL);
	return true;
}

bool Engine::SwapChain::Release()
{
	m_DXGISwapChain->Release();
	return true;
}