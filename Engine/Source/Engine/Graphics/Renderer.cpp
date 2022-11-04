#include "pch.h"
#include "Renderer.h"

#include "Framebuffer.h"

#include "Engine/Core/Debug.h"
#include "Engine/Core/Window.h"

#include "../../../Dependencies/ImGui/imgui_impl_dx11.h"

namespace Engine
{
	UniquePtr<SwapChain> Renderer::s_SwapChain = nullptr;

	UniquePtr<DeviceContext> Renderer::s_DeviceContext = nullptr;

	IDXGIDevice* Renderer::s_DxgiDevice = nullptr;

	IDXGIAdapter* Renderer::s_DxgiAdapter = nullptr;

	IDXGIFactory* Renderer::s_DxgiFactory = nullptr;

	D3D_FEATURE_LEVEL Renderer::s_FeatureLevel;

	ID3D11Device* Renderer::s_Device = nullptr;

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

	void Renderer::Start(Window& window)
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
			                           &s_Device,
			                           &s_FeatureLevel,
			                           &deviceContext);
			if (SUCCEEDED(result))
				break;
		}

		Debug::Assert(SUCCEEDED(result), "Failed to create device!");

		s_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);

		s_Device->QueryInterface(__uuidof(IDXGIDevice),
		                         reinterpret_cast<void**>(&s_DxgiDevice));

		s_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                        reinterpret_cast<void**>(&s_DxgiAdapter));

		s_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                         reinterpret_cast<void**>(&s_DxgiFactory));

		s_SwapChain = CreateUniquePtr<SwapChain>(window, s_Device, s_DxgiFactory);

		const Vector2Int winSize = Vector2Int(window.WindowRect().Width,
		                                      window.WindowRect().Height);

		s_DeviceContext->SetViewportSize(winSize);

		ImGui_ImplDX11_Init(s_Device, deviceContext);
	}

	void Renderer::End()
	{
		s_SwapChain->Release();
		s_DxgiAdapter->Release();
		s_DxgiDevice->Release();
		s_DxgiFactory->Release();
		s_DeviceContext->Release();
		s_Device->Release();
	}

	void Renderer::StartRender(const Framebuffer& framebuffer)
	{
		ID3D11RenderTargetView& renderTarget = framebuffer.GetRenderTarget();
		ID3D11DepthStencilView& depthStencil = framebuffer.GetDepthStencil();

		s_DeviceContext->ClearRenderTargetView(renderTarget,
		                                       Color(0.5f, 0.3f, 0.8f, 1.0f));

		s_DeviceContext->ClearDepthStencilView(depthStencil);

		s_DeviceContext->SetRenderTargetTo(&renderTarget,
		                                   &depthStencil);
	}

	void Renderer::EndRender(const Framebuffer& framebuffer)
	{
		// Unbound render target?
	}

	void Renderer::ClearFramebuffer(const Framebuffer& framebuffer)
	{
		ID3D11RenderTargetView& renderTarget = framebuffer.GetRenderTarget();
		ID3D11DepthStencilView& depthStencil = framebuffer.GetDepthStencil();

		s_DeviceContext->ClearRenderTargetView(renderTarget,
											   Color(0.5f, 0.3f, 0.8f, 1.0f));

		s_DeviceContext->ClearDepthStencilView(depthStencil);
	}

	void Renderer::SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
	                                 ID3D11DepthStencilView* depthStencil)
	{
		s_DeviceContext->SetRenderTargetTo(renderTarget,
		                                   depthStencil);
	}

	HRESULT Renderer::CreateBuffer(const D3D11_BUFFER_DESC* desc,
	                               const D3D11_SUBRESOURCE_DATA* resource,
	                               ID3D11Buffer** buffer)
	{
		return s_Device->CreateBuffer(desc, resource, buffer);
	}

	HRESULT Renderer::CreateLayout(const D3D11_INPUT_ELEMENT_DESC* desc,
	                               uint32_t elementCount,
	                               const void* shaderByteCode,
	                               uint32_t shaderByteCodeSize,
	                               ID3D11InputLayout** layout)
	{
		return s_Device->CreateInputLayout(desc, elementCount, shaderByteCode, shaderByteCodeSize, layout);
	}

	HRESULT Renderer::CreateVertexShader(const void* shaderByteCode,
	                                     size_t bytecodeLength,
	                                     ID3D11VertexShader** vertexShader)
	{
		return s_Device->CreateVertexShader(shaderByteCode, bytecodeLength, nullptr, vertexShader);
	}

	HRESULT Renderer::CreatePixelShader(const void* shaderByteCode,
	                                    size_t bytecodeLength,
	                                    ID3D11PixelShader** pixelShader)
	{
		return s_Device->CreatePixelShader(shaderByteCode, bytecodeLength, nullptr, pixelShader);
	}

	void Renderer::Resize(Vector2Uint& size)
	{
		if (s_SwapChain == nullptr)
			return;

	//	s_SwapChain->ResizeBuffers(size, *s_DeviceContext, s_Device);
	}

	void Renderer::SetViewportSize(const Vector2Int& viewportSize)
	{
		s_DeviceContext->SetViewportSize(viewportSize);
	}

	void Renderer::Draw(const VertexShader& vertexShader,
	                    const PixelShader& pixelShader,
	                    const VertexBuffer& vertexBuffer,
	                    const IndexBuffer& indexBuffer,
	                    const ConstantBuffer& constantBuffer,
	                    const void* updatedConstantBuffer,
	                    D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		s_DeviceContext->SetRenderData<VertexShader>(vertexShader);
		s_DeviceContext->SetRenderData<PixelShader>(pixelShader);

		s_DeviceContext->UploadShaderData<VertexShader>(constantBuffer);

		s_DeviceContext->UploadShaderData<PixelShader>(constantBuffer);

		s_DeviceContext->SetRenderData<VertexBuffer>(vertexBuffer);
		s_DeviceContext->SetRenderData<IndexBuffer>(indexBuffer);

		// Set drawing process
		// Device Context sets Draw Topology
		s_DeviceContext->SetTopology(topology);

		// Actual drawing into the frame buffer
		s_DeviceContext->DrawIndexed(indexBuffer.ElementCount(),
		                             0);
	}

	void Renderer::ShowFrame()
	{
		s_SwapChain->Present(0);
	}

	void Renderer::UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
	                                    const void* updatedBufferData)
	{
		s_DeviceContext->UpdateBufferResource(constantBuffer.m_Data, updatedBufferData);
	}

	void Renderer::Draw(const VertexShader& vertexShader,
	                    const PixelShader& pixelShader,
	                    const VertexBuffer& vertexBuffer,
	                    const IndexBuffer& indexBuffer,
	                    const D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		s_DeviceContext->SetRenderData<VertexShader>(vertexShader);
		s_DeviceContext->SetRenderData<PixelShader>(pixelShader);

		s_DeviceContext->SetRenderData<VertexBuffer>(vertexBuffer);
		s_DeviceContext->SetRenderData<IndexBuffer>(indexBuffer);

		// Set drawing process
		// Device Context sets Draw Topology
		s_DeviceContext->SetTopology(topology);

		// Actual drawing into the frame buffer
		s_DeviceContext->DrawIndexed(indexBuffer.ElementCount(),
		                             0);
	}
}
