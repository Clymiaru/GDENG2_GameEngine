#include "pch.h"

#include "Engine/Graphics/DeviceContext.h"

#include "ShaderLibrary.h"


#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/VertexShader.h"

namespace Engine
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(std::move(deviceContext)),
		m_Topology{}
	{
	}

	DeviceContext::~DeviceContext() = default;

	void DeviceContext::Release() const
	{
		m_DeviceContext->Release();
	}

	ID3D11DeviceContext& DeviceContext::Context() const
	{
		return *m_DeviceContext;
	}

	void DeviceContext::Clear(const SwapChain& swapChain,
	                          const Color color) const
	{
		m_DeviceContext->ClearRenderTargetView(&swapChain.GetRenderTargetView(),
		                                       (const float*)color);

		std::vector<ID3D11RenderTargetView*> renderTargetViews = {};
		renderTargetViews.push_back(&swapChain.GetRenderTargetView());

		m_DeviceContext->ClearDepthStencilView(&swapChain.GetDepthStencilView(),
											   D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);


		m_DeviceContext->OMSetRenderTargets(1,
		                                    renderTargetViews.data(),
		                                    &swapChain.GetDepthStencilView());
	}

	void DeviceContext::SetViewportSize(const Vector2Float& size) const
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = size.x;
		viewport.Height         = size.y;
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);

	}

	void DeviceContext::SetViewportSize(const Vector2Int& size) const
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = (FLOAT)size.x;
		viewport.Height         = (FLOAT)size.y;
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	// void DeviceContext::UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
	//                                          const void* updatedBufferData)
	// {
	// 	m_DeviceContext->UpdateSubresource(constantBuffer.m_Data,
	// 	                                   NULL,
	// 	                                   nullptr,
	// 	                                   updatedBufferData,
	// 	                                   NULL,
	// 	                                   NULL);
	// }

	void DeviceContext::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology)
	{
		m_Topology = topology;
		m_DeviceContext->IASetPrimitiveTopology(m_Topology);
	}

	void DeviceContext::DrawIndexed(const uint32_t indexCount,
	                                const uint32_t startingIndex) const
	{
		ENGINE_ASSERT_TRUE(m_Topology != D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED, L"Please set Topology before drawing!")
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
