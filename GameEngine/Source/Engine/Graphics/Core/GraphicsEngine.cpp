#include "GraphicsEngine.h"
#include <d3dcompiler.h>
#include <vector>

#include "IRenderable.h"

#include "Engine/Graphics/Core/ConstantBuffer.h"
#include "Engine/Graphics/Core/DeviceContext.h"
#include "Engine/Graphics/Core/PixelShader.h"
#include "Engine/Graphics/Core/SwapChain.h"
#include "Engine/Graphics/Core/VertexBuffer.h"
#include "Engine/Graphics/Core/VertexShader.h"
#include "Engine/Utils/Debug.h"

Engine::GraphicsEngine::GraphicsEngine() :
	m_D3DDevice(nullptr),
	m_SwapChain{nullptr},
	m_FeatureLevel(D3D_FEATURE_LEVEL_11_0),
	m_DxgiDevice{nullptr},
	m_DxgiAdapter{nullptr},
	m_DxgiFactory{nullptr},
	m_DeviceContext(nullptr)
{
}

Engine::GraphicsEngine::GraphicsEngine(GraphicsEngine const&) :
	m_D3DDevice{nullptr},
	m_SwapChain{nullptr},
	m_FeatureLevel{},
	m_DxgiDevice{nullptr},
	m_DxgiAdapter{nullptr},
	m_DxgiFactory{nullptr},
	m_DeviceContext{nullptr}
{
}

Engine::GraphicsEngine::GraphicsEngine(const GraphicsEngine&&) noexcept:
	m_D3DDevice{nullptr},
	m_FeatureLevel{},
	m_DxgiDevice{nullptr},
	m_DxgiAdapter{nullptr},
	m_DxgiFactory{nullptr},
	m_DeviceContext{nullptr}
{
}

auto Engine::GraphicsEngine::Init(HWND windowHandle,
                                  const Vector2Int& windowSize) -> void
{
	const std::vector driverTypes =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	const std::vector featureLevels =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT result = 0;

	for (const auto& driverType : driverTypes)
	{
		result = D3D11CreateDevice(nullptr,
		                           driverType,
		                           nullptr,
		                           NULL,
		                           featureLevels.data(),
		                           static_cast<UINT>(featureLevels.size()),
		                           D3D11_SDK_VERSION,
		                           &m_D3DDevice,
		                           &m_FeatureLevel,
		                           &m_DeviceContext);
		if (SUCCEEDED(result))
			break;
	}

	ENGINE_ASSERT(SUCCEEDED(result), "Failed to create device!")

	m_ImmediateDeviceContext = CreateScope<DeviceContext>(m_DeviceContext);

	m_D3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_DxgiDevice));

	m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_DxgiAdapter));

	m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_DxgiFactory));

	m_SwapChain = CreateSwapChain();
	m_SwapChain->Init(windowHandle, windowSize);
}

auto Engine::GraphicsEngine::Release() const -> void
{
	m_SwapChain->Release();

	for (auto& element : m_RenderList)
	{
		element->Release();
	}

	if (m_VertexShader)
		m_VertexShader->Release();
	if (m_PixelShader)
		m_PixelShader->Release();

	m_DxgiDevice->Release();
	m_DxgiAdapter->Release();
	m_DxgiFactory->Release();
	m_ImmediateDeviceContext->Release();
	m_D3DDevice->Release();
}

auto Engine::GraphicsEngine::Clear(const Color32 fillColor) -> void
{
	GetInstance().GetImmediateDeviceContext()->ClearRenderTarget(GetInstance().m_SwapChain, fillColor);
}

auto Engine::GraphicsEngine::SetViewportSize(const UINT width,
                                             const UINT height) -> void
{
	GetInstance().GetImmediateDeviceContext()->SetViewportSize(width,
	                                                           height);
}

auto Engine::GraphicsEngine::Draw() -> void
{
	for (const auto& renderable : GetInstance().m_RenderList)
	{
		const auto& vb = renderable->GetVertexBuffer();
		GetInstance().GetImmediateDeviceContext()->SetVertexBuffer(vb);
		GetInstance().GetImmediateDeviceContext()->DrawTriangleList(vb->GetVertexListSize(),
		                                                            0);
	}

	GetInstance().m_SwapChain->Present(true);
}

auto Engine::GraphicsEngine::RegisterRenderable(const Ref<IRenderable>& toRegister) -> void
{
	
	GetInstance().m_RenderList.push_back(toRegister);
}

auto Engine::GraphicsEngine::CreateVertexBuffer() const -> Scope<VertexBuffer>
{
	return CreateScope<VertexBuffer>();
}

auto Engine::GraphicsEngine::CreateConstantBuffer() const -> Scope<ConstantBuffer>
{
	return CreateScope<ConstantBuffer>();
}

auto Engine::GraphicsEngine::CreateVertexShader(const void* shaderByteCode,
                                                size_t byteCodeSize) const -> Scope<VertexShader>
{
	auto vs = CreateScope<VertexShader>(shaderByteCode, byteCodeSize);
	return vs;
}

auto Engine::GraphicsEngine::CreatePixelShader(const void* shaderByteCode,
                                               size_t byteCodeSize) const -> Scope<PixelShader>
{
	auto ps = CreateScope<PixelShader>(shaderByteCode, byteCodeSize);
	return ps;
}

auto Engine::GraphicsEngine::CompileVertexShader(const std::wstring& fileName,
                                                 const std::string& entryPointName,
                                                 void** shaderByteCode,
                                                 size_t* byteCodeSize) -> bool
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(
		D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, entryPointName.c_str(), "vs_5_0", 0, 0, &m_Blob, &
			errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Vertex shader cannot be compiled! (" << (char*)errorBlob->GetBufferPointer() << ")\n";
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob->GetBufferPointer();
	*byteCodeSize   = m_Blob->GetBufferSize();
	return true;
}

auto Engine::GraphicsEngine::CompilePixelShader(const std::wstring& fileName,
                                                const std::string& entryPointName,
                                                void** shaderByteCode,
                                                size_t* byteCodeSize) -> bool
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(
		D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, entryPointName.c_str(), "ps_5_0", 0, 0, &m_Blob, &
			errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Pixel shader cannot be compiled! (" << (char*)errorBlob->GetBufferPointer() << ")\n";
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob->GetBufferPointer();
	*byteCodeSize   = m_Blob->GetBufferSize();
	return true;
}

auto Engine::GraphicsEngine::ReleaseCompiledShader() const -> void
{
	if (m_Blob)
		m_Blob->Release();
}

auto Engine::GraphicsEngine::CreateSwapChain() const -> Scope<SwapChain>
{
	return CreateScope<SwapChain>();
}

auto Engine::GraphicsEngine::GetImmediateDeviceContext() -> const Scope<DeviceContext>&
{
	return m_ImmediateDeviceContext;
}

auto Engine::GraphicsEngine::GetInstance() -> GraphicsEngine&
{
	static GraphicsEngine engine;
	return engine;
}
