#include "pch.h"

#include "RenderSystem.h"

#include <d3dcompiler.h>

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/VertexBuffer.h"

auto Engine::RenderSystem::GetInstance() -> RenderSystem&
{
	static RenderSystem instance;
	return instance;
}

auto Engine::RenderSystem::Initialize(const HWND windowHandle,
                                      const Vector2Int windowSize) -> void
{
	const std::vector<D3D_DRIVER_TYPE> driverTypes =
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

	ID3D11DeviceContext* deviceContext = nullptr;

	for (const auto& driverType : driverTypes)
	{
		result = D3D11CreateDevice(nullptr,
		                           driverType,
		                           nullptr,
		                           NULL,
		                           featureLevels.data(),
		                           static_cast<UINT>(featureLevels.size()),
		                           D3D11_SDK_VERSION,
		                           &m_Device,
		                           &m_FeatureLevel,
		                           &deviceContext);
		if (SUCCEEDED(result))
			break;
	}

	// ENGINE_ASSERT(SUCCEEDED(result), "Failed to create device!")

	m_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);

	m_Device->QueryInterface(__uuidof(IDXGIDevice),
	                         reinterpret_cast<void**>(&m_DxgiDevice));

	m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
	                        reinterpret_cast<void**>(&m_DxgiAdapter));

	m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
	                         reinterpret_cast<void**>(&m_DxgiFactory));

	m_SwapChain = CreateUniquePtr<SwapChain>();
	m_SwapChain->Initialize(windowHandle,
	                        windowSize,
	                        m_Device,
	                        m_DxgiFactory);
}

auto Engine::RenderSystem::Terminate() -> void
{
	m_SwapChain->Terminate();

	for (const auto& renderObject : m_RenderList)
	{
		renderObject->VertexBuffer->Release();
	}

	m_DxgiDevice->Release();
	m_DxgiAdapter->Release();
	m_DxgiFactory->Release();
	m_DeviceContext->Terminate();
	m_Device->Release();
}

auto Engine::RenderSystem::GetDevice() -> ID3D11Device*
{
	return m_Device;
}

auto Engine::RenderSystem::GetDeviceContext() -> DeviceContext&
{
	return *m_DeviceContext;
}

auto Engine::RenderSystem::RegisterObject(void* listOfVertices,
                                          UINT vertexSize,
                                          UINT listSize,
                                          void* shaderByteCode,
                                          UINT byteShaderSize,
                                          D3D11_INPUT_ELEMENT_DESC* indexLayout,
                                          size_t indexLayoutSize) -> void
{
	const auto& obj = m_RenderList.emplace_back(CreateUniquePtr<RenderObject>(CreateUniquePtr<VertexBuffer>()));
	obj->VertexBuffer->Load(listOfVertices,
	                        vertexSize,
	                        listSize,
	                        shaderByteCode,
	                        byteShaderSize,
	                        indexLayout,
	                        indexLayoutSize);
}

auto Engine::RenderSystem::Clear(const Color32 fillColor) -> void
{
	GetInstance().m_DeviceContext->Clear(GetInstance().m_SwapChain, fillColor);
}

auto Engine::RenderSystem::Draw() -> void
{
	for (const auto& renderable : GetInstance().m_RenderList)
	{
		const auto& vb = renderable->VertexBuffer;
		GetInstance().m_DeviceContext->SetVertexBuffer(vb);
		GetInstance().m_DeviceContext->DrawTriangleList(vb->GetVertexListSize(),
		                                                0);
	}

	GetInstance().m_SwapChain->Present(true);
}

auto Engine::RenderSystem::SetViewportSize(Vector2Uint viewportSize) -> void
{
	GetInstance().m_DeviceContext->SetViewportSize(viewportSize.X, viewportSize.Y);
}

auto Engine::RenderSystem::CompileVertexShader(const std::wstring& fileName,
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
			std::cout << "Vertex shader cannot be compiled! (" << static_cast<char*>(errorBlob->GetBufferPointer()) <<
					")\n";
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob->GetBufferPointer();
	*byteCodeSize   = m_Blob->GetBufferSize();
	return true;
}

auto Engine::RenderSystem::CompilePixelShader(const std::wstring& fileName,
                                              const std::string& entryPointName,
                                              void** shaderByteCode,
                                              size_t* byteCodeSize) -> bool
{
	ID3DBlob* errorBlob = nullptr;
	if (!SUCCEEDED(
		D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, entryPointName.c_str(), "ps_5_0", 0, 0, &m_Blob2, &
			errorBlob)))
	{
		if (errorBlob)
		{
			std::cout << "Pixel shader cannot be compiled! (" << static_cast<char*>(errorBlob->GetBufferPointer()) <<
					")\n";
			errorBlob->Release();
		}
		return false;
	}

	*shaderByteCode = m_Blob2->GetBufferPointer();
	*byteCodeSize   = m_Blob2->GetBufferSize();
	return true;
}

auto Engine::RenderSystem::ReleaseCompiledShader() const -> void
{
	if (m_Blob)
		m_Blob->Release();

	if (m_Blob2)
		m_Blob2->Release();
}

Engine::RenderSystem::RenderSystem(const RenderSystem&)
{
}

Engine::RenderSystem::RenderSystem(const RenderSystem&&) noexcept
{
}

Engine::RenderSystem::RenderSystem()
{
}
