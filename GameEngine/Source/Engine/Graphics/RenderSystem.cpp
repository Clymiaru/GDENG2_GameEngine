#include "pch.h"

#include "RenderSystem.h"

#include "Core/DeviceContext.h"
#include "Core/GraphicsEngine.h"
#include "Core/VertexBuffer.h"

auto Engine::RenderSystem::GetInstance() -> RenderSystem&
{
	static RenderSystem instance;
	return instance;
}

auto Engine::RenderSystem::Initialize(const HWND windowHandle,
                                      const Vector2Int windowSize) -> void
{
	m_SwapChain = CreateScope<SwapChain>();
	m_SwapChain->Init(windowHandle, windowSize);
}

auto Engine::RenderSystem::Release() -> void
{
	m_SwapChain->Release();

	for (const auto& renderObject : m_RenderList)
	{
		renderObject->VertexBuffer->Release();
	}
}

auto Engine::RenderSystem::RegisterObject(void* listOfVertices,
                                          UINT vertexSize,
                                          UINT listSize,
                                          void* shaderByteCode,
                                          UINT byteShaderSize) -> void
{
	const auto& obj = m_RenderList.emplace_back(CreateScope<RenderObject>(CreateScope<VertexBuffer>()));
	obj->VertexBuffer->Load(listOfVertices,
	                        vertexSize,
	                        listSize,
	                        shaderByteCode,
	                        byteShaderSize);
}

auto Engine::RenderSystem::Clear(const Color32 fillColor) -> void
{
	GraphicsEngine::GetInstance().GetImmediateDeviceContext()->ClearRenderTarget(GetInstance().m_SwapChain, fillColor);
}

auto Engine::RenderSystem::Draw() -> void
{
	for (const auto& renderable : GetInstance().m_RenderList)
	{
		const auto& vb = renderable->VertexBuffer;
		GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexBuffer(vb);
		GraphicsEngine::GetInstance().GetImmediateDeviceContext()->DrawTriangleList(vb->GetVertexListSize(),
		                                                                            0);
	}

	GetInstance().m_SwapChain->Present(true);
}

auto Engine::RenderSystem::SetViewportSize(Vector2Uint viewportSize) -> void
{
}

Engine::RenderSystem::RenderSystem(const RenderSystem&)
{
}

Engine::RenderSystem::RenderSystem(const RenderSystem&&) noexcept
{
}

Engine::RenderSystem::RenderSystem()
{
}
