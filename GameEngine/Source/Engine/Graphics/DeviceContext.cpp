#include "pch.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"

namespace Engine
{
	DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
		m_DeviceContext(deviceContext)
	{
	}

	auto DeviceContext::Initialize() -> void
	{
	}

	auto DeviceContext::Terminate() -> void
	{
		m_DeviceContext->Release();
	}

	auto DeviceContext::Clear(const UniquePtr<SwapChain>& swapChain,
	                          const Color32 color) const -> void
	{
		const float clearColor[] = {color.Red, color.Green, color.Blue, color.Alpha};
		m_DeviceContext->ClearRenderTargetView(swapChain->GetRenderTargetView(),
		                                       clearColor);

		std::vector<ID3D11RenderTargetView*> renderTargetViews = {};
		renderTargetViews.push_back(swapChain->GetRenderTargetView());

		m_DeviceContext->OMSetRenderTargets(1,
		                                    (renderTargetViews.data()),
		                                    nullptr);
	}

	auto DeviceContext::SetViewportSize(const UINT width,
	                                    const UINT height) const -> void
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width          = static_cast<FLOAT>(width);
		viewport.Height         = static_cast<FLOAT>(height);
		viewport.MinDepth       = 0.0f;
		viewport.MaxDepth       = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewport);
	}

	auto DeviceContext::SetVertexBuffer(const UniquePtr<VertexBuffer>& vertexBuffer) const -> void
	{
		const UINT stride     = vertexBuffer->m_VertexSize;
		constexpr UINT offset = 0;
		m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_Buffer, &stride, &offset);
		m_DeviceContext->IASetInputLayout(vertexBuffer->m_Layout);
	}

	auto DeviceContext::SetConstantBuffer(const UniquePtr<VertexShader>& vertexShader,
	                                      const UniquePtr<ConstantBuffer>& constantBuffer) const -> void
	{
		m_DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer->m_BufferData);
	}

	auto DeviceContext::SetConstantBuffer(const UniquePtr<PixelShader>& pixelShader,
	                                      const UniquePtr<ConstantBuffer>& constantBuffer) const -> void
	{
		m_DeviceContext->PSSetConstantBuffers(0, 1, &constantBuffer->m_BufferData);
	}

	auto DeviceContext::SetVertexShader(const UniquePtr<VertexShader>& vertexShader) const -> void
	{
		m_DeviceContext->VSSetShader(vertexShader->m_Data, nullptr, 0);
	}

	auto DeviceContext::SetPixelShader(const UniquePtr<PixelShader>& pixelShader) const -> void
	{
		m_DeviceContext->PSSetShader(pixelShader->m_Data, nullptr, 0);
	}

	auto DeviceContext::DrawTriangleList(UINT vertexCount,
	                                     UINT startVertexIndex) const -> void
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_DeviceContext->Draw(vertexCount, startVertexIndex);
	}

	auto DeviceContext::DrawTriangleStrip(UINT vertexCount,
	                                      UINT startVertexIndex) const -> void
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_DeviceContext->Draw(vertexCount, startVertexIndex);
	}
}
