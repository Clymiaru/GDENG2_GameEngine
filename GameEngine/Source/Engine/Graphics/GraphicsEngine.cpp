#include "GraphicsEngine.h"
#include <vector>

#include "Engine/Utils/Debug.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/VertexBuffer.h"

#include <d3dcompiler.h>

Engine::GraphicsEngine::GraphicsEngine() :
	m_D3DDevice(nullptr),
	m_FeatureLevel(D3D_FEATURE_LEVEL_11_0),
	m_DeviceContext(nullptr)
{
}

void Engine::GraphicsEngine::Init(HWND windowHandle, const Engine::Vector2Int& windowSize)
{
	std::vector<D3D_DRIVER_TYPE> driverTypes =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	std::vector<D3D_FEATURE_LEVEL> featureLevels =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT result = 0;
	for (size_t i = 0; i < driverTypes.size(); ++i)
	{
		result = D3D11CreateDevice(NULL,
			driverTypes[i],
			NULL,
			NULL,
			featureLevels.data(),
			featureLevels.size(),
			D3D11_SDK_VERSION,
			&m_D3DDevice,
			&m_FeatureLevel,
			&m_DeviceContext);

		if (SUCCEEDED(result))
			break;
	}

	ENGINE_ASSERT(SUCCEEDED(result), "Failed to create device!");

	m_ImmediateDeviceContext = CreateScope<DeviceContext>(m_DeviceContext);

	m_D3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_DXGIDevice);
	m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&m_DXGIAdapter);
	m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_DXGIFactory);

	auto swapChainResult = InitSwapChain(windowHandle, windowSize);

	ENGINE_ASSERT(swapChainResult, "Failed to create Swap Chain!");
}

void Engine::GraphicsEngine::Release()
{
	if (m_VS)
		m_VS->Release();
	if (m_PS)
		m_PS->Release();

	if (m_VSblob)
		m_VSblob->Release();
	if (m_PSblob)
		m_PSblob->Release();

	m_SwapChain->Release();

	m_DXGIDevice->Release();
	m_DXGIAdapter->Release();
	m_DXGIFactory->Release();

	m_ImmediateDeviceContext->Release();
	m_D3DDevice->Release();
}

void Engine::GraphicsEngine::Clear(Color32 fillColor)
{
	GetInstance().GetImmediateDeviceContext()->ClearRenderTarget(&*m_SwapChain, { 1.0f, 0.0f, 1.0f, 1.0f });
}

void Engine::GraphicsEngine::Draw()
{
	m_SwapChain->Present(false);
}

Engine::VertexBuffer* Engine::GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

bool Engine::GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_VSblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_PSblob, &errblob);
	m_D3DDevice->CreateVertexShader(m_VSblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_VS);
	m_D3DDevice->CreatePixelShader(m_PSblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_PS);
	return true;
}

bool Engine::GraphicsEngine::SetShaders()
{
	m_ImmediateDeviceContext->VSSetShader(m_VS, nullptr, 0);
	m_ImmediateDeviceContext->PSSetShader(m_PS, nullptr, 0);
	return true;
}

void Engine::GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_VSblob->GetBufferPointer();
	*size = (UINT)this->m_VSblob->GetBufferSize();
}

bool Engine::GraphicsEngine::InitSwapChain(HWND windowHandle, const Engine::Vector2Int& windowSize)
{
	m_SwapChain = CreateScope<SwapChain>();
	m_SwapChain->Init(windowHandle, windowSize);
	return true;
}

Engine::GraphicsEngine::~GraphicsEngine()
{
}

Engine::Scope<Engine::SwapChain> Engine::GraphicsEngine::CreateSwapChain()
{
	return CreateScope<SwapChain>();
}

const Engine::Scope<Engine::DeviceContext>& Engine::GraphicsEngine::GetImmediateDeviceContext()
{
	return m_ImmediateDeviceContext;
}

Engine::GraphicsEngine& Engine::GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;
	return engine;
}
