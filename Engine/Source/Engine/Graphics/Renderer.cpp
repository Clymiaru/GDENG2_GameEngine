#include "pch.h"
#include "Renderer.h"

#include "Buffer/Framebuffer.h"

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

	Renderer::Renderer()
	{
		HRESULT result = 0;

		ID3D11DeviceContext* deviceContext = nullptr;
		ID3D11Device* device = nullptr;

		for (const auto& driverType : DRIVER_TYPES_SUPPORTED)
		{
			result = D3D11CreateDevice(nullptr,
			                           driverType,
			                           nullptr,
			                           NULL,
			                           FEATURE_LEVELS_SUPPORTED.data(),
			                           static_cast<UINT>(FEATURE_LEVELS_SUPPORTED.size()),
			                           D3D11_SDK_VERSION,
			                           &device,
			                           &m_FeatureLevel,
			                           &deviceContext);
			if (SUCCEEDED(result))
				break;
		}

		Debug::Assert(SUCCEEDED(result), "Failed to create device!");

		m_Context = new RenderContext(deviceContext);

		m_Device = new RenderDevice(device);
	}

	Renderer::~Renderer()
	{
		delete m_Context;
		delete m_Device;
	}

	void Renderer::StartRender(const Framebuffer& framebuffer)
	{
		SetViewportSize(Vector2Uint(framebuffer.GetInfo().Width,
		                            framebuffer.GetInfo().Height));

		SetFramebuffer(framebuffer);

		ClearFramebuffer(framebuffer);
	}

	void Renderer::EndRender()
	{
		// Unbound render target?
		m_Context->SetRenderTargetTo(nullptr, nullptr);
	}

	void Renderer::SetViewportSize(const Vector2Uint& viewportSize) const
	{
		m_Context->SetViewportSize(viewportSize);
	}

	void Renderer::SetFramebuffer(const Framebuffer& framebuffer)
	{
		ID3D11RenderTargetView& renderTarget = framebuffer.GetRenderTarget();
		ID3D11DepthStencilView& depthStencil = framebuffer.GetDepthStencil();
		m_Context->SetRenderTargetTo(&renderTarget, &depthStencil);
	}

	void Renderer::ClearFramebuffer(const Framebuffer& framebuffer)
	{
		ID3D11RenderTargetView& renderTarget = framebuffer.GetRenderTarget();
		ID3D11DepthStencilView& depthStencil = framebuffer.GetDepthStencil();

		m_Context->ClearRenderTargetView(renderTarget,
		                                       Color(0.5f, 0.3f, 0.8f, 1.0f));

		m_Context->ClearDepthStencilView(depthStencil);
	}

	RenderDevice& Renderer::GetDevice() const
	{
		return *m_Device;
	}
	
	RenderContext& Renderer::GetContext() const
	{
		return *m_Context;
	}
	
	void Renderer::UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
	                                    const void* updatedBufferData)
	{
		m_Context->UpdateBufferResource(constantBuffer.m_Data, updatedBufferData);
	}
}
