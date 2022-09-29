#include "pch.h"

#include "Engine/Graphics/Core/DeviceContext.h"
#include "Engine/Graphics/Core/ConstantBuffer.h"
#include "Engine/Graphics/Core/PixelShader.h"
#include "Engine/Graphics/Core/SwapChain.h"
#include "Engine/Graphics/Core/VertexBuffer.h"
#include "Engine/Graphics/Core/VertexShader.h"

Engine::DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
	m_DeviceContext(deviceContext)
{
}

auto Engine::DeviceContext::Release() const -> void
{
	m_DeviceContext->Release();
}

auto Engine::DeviceContext::ClearRenderTarget(const Scope<SwapChain>& swapChain,
                                              const Color32 color) const -> void
{
	const FLOAT clearColor[] = {color.Red, color.Green, color.Blue, color.Alpha};
	m_DeviceContext->ClearRenderTargetView(swapChain->m_RenderTargetView, clearColor);
	m_DeviceContext->OMSetRenderTargets(1, &(swapChain->m_RenderTargetView), nullptr);
}

auto Engine::DeviceContext::SetVertexBuffer(const Scope<VertexBuffer>& vertexBuffer) const -> void
{
	const UINT stride = vertexBuffer->m_VertexSize;
	const UINT offset = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_Buffer, &stride, &offset);
	m_DeviceContext->IASetInputLayout(vertexBuffer->m_Layout);
}

auto Engine::DeviceContext::SetConstantBuffer(const Scope<VertexShader>& vertexShader,
                                              const Scope<ConstantBuffer>& constantBuffer) const -> void
{
	m_DeviceContext->VSSetConstantBuffers(0, 1, &constantBuffer->m_BufferData);
}

auto Engine::DeviceContext::SetConstantBuffer(const Scope<PixelShader>& pixelShader,
                                              const Scope<ConstantBuffer>& constantBuffer) const -> void
{
	m_DeviceContext->PSSetConstantBuffers(0, 1, &constantBuffer->m_BufferData);
}

auto Engine::DeviceContext::SetVertexShader(const Scope<VertexShader>& vertexShader) const -> void
{
	m_DeviceContext->VSSetShader(vertexShader->m_Data, nullptr, 0);
}

auto Engine::DeviceContext::SetPixelShader(const Scope<PixelShader>& pixelShader) const -> void
{
	m_DeviceContext->PSSetShader(pixelShader->m_Data, nullptr, 0);
}

auto Engine::DeviceContext::DrawTriangleList(UINT vertexCount,
                                             UINT startVertexIndex) const -> void
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_DeviceContext->Draw(vertexCount, startVertexIndex);
}

auto Engine::DeviceContext::DrawTriangleStrip(UINT vertexCount,
                                              UINT startVertexIndex) const -> void
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_DeviceContext->Draw(vertexCount, startVertexIndex);
}

auto Engine::DeviceContext::SetViewportSize(const UINT width,
                                            const UINT height) const -> void
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width          = static_cast<FLOAT>(width);
	viewport.Height         = static_cast<FLOAT>(height);
	viewport.MinDepth       = 0.0f;
	viewport.MaxDepth       = 1.0f;
	m_DeviceContext->RSSetViewports(1, &viewport);
}
