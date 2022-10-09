#include "pch.h"

#include "Engine/Graphics/DeviceContext.h"

#include "ShaderLibrary.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"

namespace Engine
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(std::move(deviceContext))
	{
	}

	DeviceContext::~DeviceContext() = default;

	auto DeviceContext::Initialize() -> void
	{
	}

	auto DeviceContext::Terminate() -> void
	{
		m_DeviceContext->Release();
	}

	auto DeviceContext::Clear(const SwapChain& swapChain,
	                          const Color32 color) const -> void
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

	auto DeviceContext::SetViewportSize(const Vector2Uint size) const -> void
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = static_cast<float>(size.X);
		viewport.Height         = static_cast<float>(size.Y);
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	auto DeviceContext::SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) -> void
	{
		m_Topology = topology;
		m_DeviceContext->IASetPrimitiveTopology(m_Topology);
	}

	auto DeviceContext::Draw(const Uint indexCount,
	                         const Uint startingIndex) const -> void
	{
		ENGINE_ASSERT(m_Topology != D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED, "Please set Topology before drawing!")
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
