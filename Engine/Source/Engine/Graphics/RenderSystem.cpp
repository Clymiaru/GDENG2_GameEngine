﻿#include "pch.h"
#include "RenderSystem.h"

#include "Engine/Core/Debug.h"

#include "DeviceContext.h"

#include "SwapChain.h"
#include "../../../Dependencies/ImGui/imgui_impl_dx11.h"

#include "Engine/Core/Window.h"

namespace Engine
{
	RenderSystem RenderSystem::m_Instance = RenderSystem();

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

	void RenderSystem::Start(Window& window)
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
			                           &m_Instance.m_Device,
			                           &m_Instance.m_FeatureLevel,
			                           &deviceContext);
			if (SUCCEEDED(result))
				break;
		}

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create device!")

		m_Instance.m_Device->QueryInterface(__uuidof(IDXGIDevice),
		                                    reinterpret_cast<void**>(&m_Instance.m_DxgiDevice));

		m_Instance.m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                                   reinterpret_cast<void**>(&m_Instance.m_DxgiAdapter));

		m_Instance.m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                                    reinterpret_cast<void**>(&m_Instance.m_DxgiFactory));

		m_Instance.m_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);
		m_Instance.m_SwapChain     = CreateUniquePtr<SwapChain>(window,
																m_Instance.m_Device,
																m_Instance.m_DxgiFactory);
		
		GetDeviceContext().SetViewportSize(window.GetSize());
		ImGui_ImplDX11_Init(m_Instance.m_Device, m_Instance.m_DeviceContext->m_DeviceContext);
	}

	void RenderSystem::End()
	{
		m_Instance.m_SwapChain->Release();

		m_Instance.m_DxgiDevice->Release();
		m_Instance.m_DxgiAdapter->Release();
		m_Instance.m_DxgiFactory->Release();

		m_Instance.m_DeviceContext->Release();

		m_Instance.m_Device->Release();
	}

	ID3D11Device& RenderSystem::GetDevice()
	{
		return *m_Instance.m_Device;
	}

	DeviceContext& RenderSystem::GetDeviceContext()
	{
		return *m_Instance.m_DeviceContext;
	}

	void RenderSystem::Clear(const Color fillColor)
	{
		m_Instance.m_DeviceContext->Clear(*m_Instance.m_SwapChain, fillColor);
	}

	void RenderSystem::Draw(const VertexBuffer& vertexBuffer,
	                        const IndexBuffer& indexBuffer)
	{
		m_Instance.m_DeviceContext->SetBuffer<VertexBuffer>(vertexBuffer);
		m_Instance.m_DeviceContext->SetBuffer<IndexBuffer>(indexBuffer);
		m_Instance.m_DeviceContext->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Instance.m_DeviceContext->DrawIndexed(indexBuffer.ElementCount(), 0);
	}

	void RenderSystem::Draw(const RenderData& data)
	{
	}

	void RenderSystem::ShowFrame()
	{
		m_Instance.m_SwapChain->Present(true);
	}

	void RenderSystem::SetViewportSize(Vector2 viewportSize)
	{
		m_Instance.m_DeviceContext->SetViewportSize(viewportSize);
	}

	RenderSystem::RenderSystem() :
		m_SwapChain{nullptr},
		m_DeviceContext{nullptr},
		m_Device{nullptr},
		m_FeatureLevel{},
		m_DxgiDevice{nullptr},
		m_DxgiAdapter{nullptr},
		m_DxgiFactory{nullptr}
	{
	}

	RenderSystem::~RenderSystem() = default;
}
