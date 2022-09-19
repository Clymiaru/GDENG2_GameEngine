#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

Engine::DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
	m_DeviceContext(deviceContext)
{
}

Engine::DeviceContext::~DeviceContext()
{
}

bool Engine::DeviceContext::Release()
{
	m_DeviceContext->Release();
	return true;
}

void Engine::DeviceContext::ClearRenderTarget(SwapChain* swapChain, Color32 color)
{
	FLOAT clearColor[] = { color.Red, color.Green, color.Blue, color.Alpha };
	m_DeviceContext->ClearRenderTargetView(swapChain->m_RenderTargetView, clearColor);
	m_DeviceContext->OMGetRenderTargets(1, &swapChain->m_RenderTargetView, NULL, )
}

void Engine::DeviceContext::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_VertexSize;
	UINT offset = 0;

	m_DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_Buffer, &stride, &offset);
	m_DeviceContext->IASetInputLayout(vertexBuffer->m_Layout);
}

void Engine::DeviceContext::DrawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_DeviceContext->Draw(vertexCount, startVertexIndex);
}

void Engine::DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports(1, &viewport);
}
