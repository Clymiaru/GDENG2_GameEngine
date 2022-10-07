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

	auto DeviceContext::SetVertexBuffer(const VertexBuffer& vertexBuffer) const -> void
	{
		const UINT stride     = vertexBuffer.m_DataSize;
		constexpr UINT offset = 0;
		m_DeviceContext->IASetVertexBuffers(0,
		                                    1,
		                                    &vertexBuffer.m_Data,
		                                    &stride,
		                                    &offset);
		m_DeviceContext->IASetInputLayout(vertexBuffer.m_DataLayout);
	}

	auto DeviceContext::SetIndexBuffer(const IndexBuffer& indexBuffer) const -> void
	{
		constexpr UINT offset = 0;
		m_DeviceContext->IASetIndexBuffer(indexBuffer.m_Data, DXGI_FORMAT_R32_UINT, offset);
	}

	auto DeviceContext::SetConstantBuffer(const VertexShader& vertexShader,
	                                      const ConstantBuffer& constantBuffer) const -> void
	{
		m_DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	auto DeviceContext::SetConstantBuffer(const PixelShader& pixelShader,
	                                      const ConstantBuffer& constantBuffer) const -> void
	{
		m_DeviceContext->PSSetConstantBuffers(0, 1, &constantBuffer.m_BufferData);
	}

	auto DeviceContext::SetVertexShader(const std::wstring& filename) const -> void
	{
		auto& vertexShader = ShaderLibrary::GetInstance().GetVertexShader(filename);
		m_DeviceContext->VSSetShader(&vertexShader.GetData(), nullptr, 0);
	}

	auto DeviceContext::SetPixelShader(const std::wstring& filename) const -> void
	{
		auto& pixelShader = ShaderLibrary::GetInstance().GetPixelShader(filename);
		m_DeviceContext->PSSetShader(&pixelShader.GetData(), nullptr, 0);
	}

	auto DeviceContext::DrawTriangleList(const Uint indexCount,
	                                     const Uint startingIndex) const -> void
	{
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_DeviceContext->DrawIndexed(indexCount,
		                             startingIndex,
		                             0);
	}
}
