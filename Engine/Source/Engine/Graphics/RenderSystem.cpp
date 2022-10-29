#include "pch.h"
#include "RenderSystem.h"

#include "Engine/Core/Debug.h"

#include "DeviceContext.h"

#include "SwapChain.h"
#include "../../../Dependencies/ImGui/imgui_impl_dx11.h"

#include "Engine/Core/Window.h"
#include "Engine/Math/Vector3.h"

namespace Engine
{
	IDXGIDevice* g_DxgiDevice = nullptr;

	IDXGIAdapter* g_DxgiAdapter = nullptr;

	IDXGIFactory* g_DxgiFactory = nullptr;

	D3D_FEATURE_LEVEL g_FeatureLevel;

	ID3D11Device* g_Device = nullptr;

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
			                           &g_Device,
			                           &g_FeatureLevel,
			                           &deviceContext);
			if (SUCCEEDED(result))
				break;
		}

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Failed to create device!")

		g_Device->QueryInterface(__uuidof(IDXGIDevice),
		                         reinterpret_cast<void**>(&g_DxgiDevice));

		g_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                        reinterpret_cast<void**>(&g_DxgiAdapter));

		g_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                         reinterpret_cast<void**>(&g_DxgiFactory));

		m_Instance.m_DeviceContext = CreateUniquePtr<DeviceContext>(deviceContext);
		m_Instance.m_SwapChain     = CreateUniquePtr<SwapChain>(window,
		                                                        g_Device,
		                                                        g_DxgiFactory);
		Vector2Float winSize = Vector2Float{(float)window.WindowRect().x, (float)window.WindowRect().y};
		GetDeviceContext().SetViewportSize(winSize);
		ImGui_ImplDX11_Init(g_Device, m_Instance.m_DeviceContext->m_DeviceContext);
	}

	void RenderSystem::End()
	{
		m_Instance.m_SwapChain->Release();

		g_DxgiDevice->Release();
		g_DxgiAdapter->Release();
		g_DxgiFactory->Release();

		m_Instance.m_DeviceContext->Release();

		g_Device->Release();
	}

	ID3D11Device& RenderSystem::GetDevice()
	{
		return *g_Device;
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

	void RenderSystem::Draw(VertexShader& vertexShader,
	                        PixelShader& pixelShader,
	                        const VertexBuffer& vertexBuffer,
	                        const IndexBuffer& indexBuffer,
	                        const ConstantBuffer& constantBuffer,
	                        const void* updatedConstantBuffer,
	                        D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		m_Instance.m_DeviceContext->SetShader<VertexShader>(vertexShader);
		m_Instance.m_DeviceContext->SetShader<PixelShader>(pixelShader);

		m_Instance.m_DeviceContext->SetConstantBuffer<VertexShader>(constantBuffer);
		m_Instance.m_DeviceContext->SetConstantBuffer<PixelShader>(constantBuffer);

		m_Instance.m_DeviceContext->SetBuffer<VertexBuffer>(vertexBuffer);
		m_Instance.m_DeviceContext->SetBuffer<IndexBuffer>(indexBuffer);
		m_Instance.m_DeviceContext->SetTopology(topology);
		m_Instance.m_DeviceContext->DrawIndexed(indexBuffer.ElementCount(), 0);
	}

	void RenderSystem::ShowFrame()
	{
		m_Instance.m_SwapChain->Present(true);
	}

	void RenderSystem::SetViewportSize(Vector2Int viewportSize)
	{
		m_Instance.m_DeviceContext->SetViewportSize(viewportSize);
	}

	RenderSystem::RenderSystem() :
		m_SwapChain{nullptr},
		m_DeviceContext{nullptr}
	{
	}

	RenderSystem::~RenderSystem() = default;
}
