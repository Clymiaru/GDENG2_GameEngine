#include "pch.h"

#include "Engine/Graphics/DeviceContext.h"

#include "ShaderLibrary.h"

namespace Engine
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(std::move(deviceContext))
	{
	}

	DeviceContext::~DeviceContext() = default;

	void DeviceContext::Release() const
	{
		m_DeviceContext->Release();
	}

	void DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView& renderTarget,
	                                          const Color& color) const
	{
		m_DeviceContext->ClearRenderTargetView(&renderTarget,
		                                       (const float*)color);
	}

	void DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView& depthStencilView) const
	{
		m_DeviceContext->ClearDepthStencilView(&depthStencilView,
		                                       D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	}

	void DeviceContext::SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
	                                      ID3D11DepthStencilView* depthStencil) const
	{
		int numOfRenderTarget = 1;

		if (renderTarget == nullptr)
			numOfRenderTarget = 0;

		std::vector<ID3D11RenderTargetView*> renderTargetViews = {};
		renderTargetViews.push_back(renderTarget);

		m_DeviceContext->OMSetRenderTargets(numOfRenderTarget,
		                                    renderTargetViews.data(),
		                                    depthStencil);
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

	void DeviceContext::UpdateBufferResource(ID3D11Buffer* bufferResource,
	                                         const void* updatedBufferData) const
	{
		m_DeviceContext->UpdateSubresource(bufferResource,
		                                   NULL,
		                                   nullptr,
		                                   updatedBufferData,
		                                   NULL,
		                                   NULL);
	}

	void DeviceContext::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) const
	{
		m_DeviceContext->IASetPrimitiveTopology(topology);
	}

	void DeviceContext::DrawIndexed(const uint32_t indexCount,
	                                const uint32_t startingIndex) const
	{
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
