#include "pch.h"
#include <d3dcompiler.h>

#include "RenderSystem.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Utils/Debug.h"

namespace Engine
{
	auto RenderSystem::GetInstance() -> RenderSystem&
	{
		static RenderSystem instance;
		return instance;
	}

	auto RenderSystem::Initialize(const HWND windowHandle,
	                              const Vector2Int windowSize) -> void
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

		ENGINE_ASSERT(SUCCEEDED(result), "Failed to create device!")

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

	auto RenderSystem::Terminate() const -> void
	{
		m_SwapChain->Terminate();
		m_DxgiDevice->Release();
		m_DxgiAdapter->Release();
		m_DxgiFactory->Release();
		m_DeviceContext->Terminate();
		m_Device->Release();
	}

	auto RenderSystem::GetDevice() const -> ID3D11Device&
	{
		return *m_Device;
	}

	auto RenderSystem::GetDeviceContext() const -> DeviceContext&
	{
		return *m_DeviceContext;
	}

	auto RenderSystem::Clear(const Color32 fillColor) const -> void
	{
		m_DeviceContext->Clear(*m_SwapChain, fillColor);
	}

	auto RenderSystem::Draw(const VertexBuffer& vertexBuffer,
	                        const IndexBuffer& indexBuffer) const -> void
	{
		m_DeviceContext->SetVertexBuffer(vertexBuffer);
		m_DeviceContext->SetIndexBuffer(indexBuffer);
		m_DeviceContext->DrawTriangleList(indexBuffer.GetCount(),
		                                  0);
	}

	auto RenderSystem::ShowFrame() const -> void
	{
		m_SwapChain->Present(true);
	}

	auto RenderSystem::SetViewportSize(Vector2Uint viewportSize) const -> void
	{
		m_DeviceContext->SetViewportSize(viewportSize);
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
