#include "pch.h"
#include "RenderSystem.h"

#include <d3dcompiler.h>

#include "SwapChain.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Utils/Debug.h"

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

	auto RenderSystem::Initialize(const HWND windowHandle,
	                              const Vector2Int windowSize) -> void
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

		m_Instance.m_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);

		m_Instance.m_Device->QueryInterface(__uuidof(IDXGIDevice),
		                                    reinterpret_cast<void**>(&m_Instance.m_DxgiDevice));

		m_Instance.m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                                   reinterpret_cast<void**>(&m_Instance.m_DxgiAdapter));

		m_Instance.m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                                    reinterpret_cast<void**>(&m_Instance.m_DxgiFactory));

		m_Instance.m_SwapChain = CreateUniquePtr<SwapChain>();
		m_Instance.m_SwapChain->Initialize(windowHandle,
		                                   windowSize,
		                                   m_Instance.m_Device,
		                                   m_Instance.m_DxgiFactory);
	}

	auto RenderSystem::Terminate() -> void
	{
		m_Instance.m_SwapChain->Terminate();
		m_Instance.m_DxgiDevice->Release();
		m_Instance.m_DxgiAdapter->Release();
		m_Instance.m_DxgiFactory->Release();
		m_Instance.m_DeviceContext->Terminate();
		m_Instance.m_Device->Release();
	}

	auto RenderSystem::GetDevice() -> ID3D11Device&
	{
		return *m_Instance.m_Device;
	}

	auto RenderSystem::GetDeviceContext() -> DeviceContext&
	{
		return *m_Instance.m_DeviceContext;
	}

	auto RenderSystem::Clear(const Color32 fillColor) -> void
	{
		m_Instance.m_DeviceContext->Clear(*m_Instance.m_SwapChain, fillColor);
	}

	auto RenderSystem::Draw(const VertexBuffer& vertexBuffer,
	                        const IndexBuffer& indexBuffer) -> void
	{
		m_Instance.m_DeviceContext->SetBuffer<VertexBuffer>(vertexBuffer);
		m_Instance.m_DeviceContext->SetBuffer<IndexBuffer>(indexBuffer);
		m_Instance.m_DeviceContext->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Instance.m_DeviceContext->Draw(indexBuffer.GetCount(),
		                                 0);
	}

	auto RenderSystem::ShowFrame() -> void
	{
		m_Instance.m_SwapChain->Present(true);
	}

	auto RenderSystem::SetViewportSize(Vector2Uint viewportSize) -> void
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
