#include "pch.h"
#include "Renderer.h"

#include "Engine/Core/Debug.h"
#include "Engine/Core/Window.h"

#include "../../../Dependencies/ImGui/imgui_impl_dx11.h"

namespace Engine
{
	const std::vector<D3D_DRIVER_TYPE> DRIVER_TYPES_SUPPORTED
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	const std::vector<D3D_FEATURE_LEVEL> FEATURE_LEVELS_SUPPORTED
	{
		D3D_FEATURE_LEVEL_11_0
	};

	Renderer::Renderer(Window& window)
	{
		CreateDeviceAndContext();

		m_Device->QueryInterface(__uuidof(IDXGIDevice),
								 reinterpret_cast<void**>(&m_DxgiDevice));

		m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
								reinterpret_cast<void**>(&m_DxgiAdapter));

		m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
								 reinterpret_cast<void**>(&m_DxgiFactory));

		m_SwapChain = CreateUniquePtr<SwapChain>(window, m_Device, m_DxgiFactory);

		const Vector2Int winSize = Vector2Int(window.WindowRect().Width, window.WindowRect().Height);

		m_DeviceContext->SetViewportSize(winSize);

		ImGui_ImplDX11_Init(m_Device, &m_DeviceContext->Context());
	}

	Renderer::~Renderer()
	{
		m_SwapChain->Release();
		m_DxgiAdapter->Release();
		m_DxgiDevice->Release();
		m_DxgiFactory->Release();
		m_DeviceContext->Release();
		m_Device->Release();
	}

	void Renderer::Clear(const Color& clearColor) const
	{
		m_DeviceContext->Clear(*m_SwapChain, clearColor);
	}

	void Renderer::UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
	                                    const void* updatedBufferData)
	{
		//m_DeviceContext->UpdateConstantBuffer(constantBuffer, updatedBufferData);
	}

	HRESULT Renderer::CreateBuffer(D3D11_BUFFER_DESC* desc,
	                               D3D11_SUBRESOURCE_DATA* resource,
	                               ID3D11Buffer** buffer)
	{
		return m_Device->CreateBuffer(desc, resource, buffer);
	}

	HRESULT Renderer::CreateLayout(const D3D11_INPUT_ELEMENT_DESC* desc,
	                               uint32_t elementCount,
	                               const void* shaderByteCode,
	                               uint32_t shaderByteCodeSize,
	                               ID3D11InputLayout** layout)
	{
		return m_Device->CreateInputLayout(desc, elementCount, shaderByteCode, shaderByteCodeSize, layout);
	}

	HRESULT Renderer::CreateVertexShader(const void* shaderByteCode,
	                                     size_t bytecodeLength,
	                                     ID3D11VertexShader** vertexShader) const
	{
		return m_Device->CreateVertexShader(shaderByteCode, bytecodeLength, nullptr, vertexShader);
	}

	HRESULT Renderer::CreatePixelShader(const void* shaderByteCode,
	                                    size_t bytecodeLength,
	                                    ID3D11PixelShader** pixelShader) const
	{
		return m_Device->CreatePixelShader(shaderByteCode, bytecodeLength, nullptr, pixelShader);
	}

	// void Renderer::Draw(VertexShader& vertexShader,
	//                     PixelShader& pixelShader,
	//                     const VertexBuffer& vertexBuffer,
	//                     const IndexBuffer& indexBuffer,
	//                     const ConstantBuffer& constantBuffer,
	//                     const void* updatedConstantBuffer,
	//                     D3D11_PRIMITIVE_TOPOLOGY topology)
	// {
	// 	// m_DeviceContext->SetShader<VertexShader>(vertexShader);
	// 	// m_DeviceContext->SetShader<PixelShader>(pixelShader);
	// 	//
	// 	// m_DeviceContext->SetConstantBuffer<VertexShader>(constantBuffer);
	// 	// m_DeviceContext->SetConstantBuffer<PixelShader>(constantBuffer);
	// 	//
	// 	// m_DeviceContext->SetBuffer<VertexBuffer>(vertexBuffer);
	// 	// m_DeviceContext->SetBuffer<IndexBuffer>(indexBuffer);
	// 	// m_DeviceContext->SetTopology(topology);
	// 	// m_DeviceContext->DrawIndexed(indexBuffer.ElementCount(), 0);
	// }

	void Renderer::ShowFrame() const
	{
		m_SwapChain->Present(0);
	}

	void Renderer::CreateDeviceAndContext()
	{
		HRESULT result = 0;

		ID3D11DeviceContext* deviceContext = nullptr;

		for (const auto& driverType : DRIVER_TYPES_SUPPORTED)
		{
			result = D3D11CreateDevice(nullptr,
			                           driverType,
			                           nullptr,
			                           NULL,
			                           FEATURE_LEVELS_SUPPORTED.data(),
			                           static_cast<UINT>(FEATURE_LEVELS_SUPPORTED.size()),
			                           D3D11_SDK_VERSION,
			                           &m_Device,
			                           &m_FeatureLevel,
			                           &deviceContext);
			if (SUCCEEDED(result))
				break;
		}

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), L"Failed to create device!")

		m_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);
	}
}
