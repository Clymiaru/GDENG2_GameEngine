#include "pch.h"

#include "Engine/Graphics/DeviceContext.h"

#include "ShaderLibrary.h"

#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/VertexShader.h"

namespace Engine
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(std::move(deviceContext))
	{
	}

	DeviceContext::~DeviceContext() = default;

	void DeviceContext::Initialize()
	{
	}

	void DeviceContext::Terminate() const
	{
		m_DeviceContext->Release();
	}

	void DeviceContext::Clear(const SwapChain& swapChain,
	                          const Color32 color) const
	{
		const float clearColor[] = {color.Red, color.Green, color.Blue, color.Alpha};
		m_DeviceContext->ClearRenderTargetView(&swapChain.GetRenderTargetView(),
		                                       clearColor);

		std::vector<ID3D11RenderTargetView*> renderTargetViews = {};
		renderTargetViews.push_back(&swapChain.GetRenderTargetView());

		m_DeviceContext->OMSetRenderTargets(1,
		                                    renderTargetViews.data(),
		                                    nullptr);
	}

	void DeviceContext::SetViewportSize(const Vector2Uint size) const
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = static_cast<float>(size.X);
		viewport.Height         = static_cast<float>(size.Y);
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	void DeviceContext::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology)
	{
		m_Topology = topology;
		m_DeviceContext->IASetPrimitiveTopology(m_Topology);
	}

	void DeviceContext::Draw(const Uint indexCount,
	                         const Uint startingIndex) const
	{
		ENGINE_ASSERT(m_Topology != D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED, "Please set Topology before drawing!")
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
