#include "pch.h"

#include "Engine/Graphics/RenderContext.h"

namespace Engine
{
	RenderContext::RenderContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(std::move(deviceContext))
	{
	}

	RenderContext::~RenderContext()
	{
		m_DeviceContext->Release();
	}

	void RenderContext::ClearRenderTargetView(ID3D11RenderTargetView& renderTarget,
	                                          const Color& color) const
	{
		m_DeviceContext->ClearRenderTargetView(&renderTarget,
		                                       (const float*)color);
	}

	void RenderContext::ClearDepthStencilView(ID3D11DepthStencilView& depthStencilView) const
	{
		m_DeviceContext->ClearDepthStencilView(&depthStencilView,
		                                       D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	}

	void RenderContext::SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
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

	void RenderContext::SetViewportSize(const Vector2Uint& size) const
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = (FLOAT)size.x;
		viewport.Height         = (FLOAT)size.y;
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	void RenderContext::SetViewportSize(const Vector2Float& size) const
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = size.x;
		viewport.Height         = size.y;
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	void RenderContext::UpdateBufferResource(ID3D11Buffer* bufferResource,
	                                         const void* updatedBufferData) const
	{
		m_DeviceContext->UpdateSubresource(bufferResource,
		                                   NULL,
		                                   nullptr,
		                                   updatedBufferData,
		                                   NULL,
		                                   NULL);
	}

	void RenderContext::DrawIndexed(const uint32_t indexCount,
	                                const uint32_t startingIndex) const
	{
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
