#include "IRenderable.h"

Engine::IRenderable::IRenderable(void* listOfVertices,
								 UINT vertexSize,
								 UINT listSize,
								 void* shaderByteCode,
								 UINT byteShaderSize)
{
	m_VertexBuffer = CreateScope<VertexBuffer>();
	m_VertexBuffer->Load(listOfVertices, vertexSize, listSize, shaderByteCode, byteShaderSize);
}

Engine::IRenderable::~IRenderable()
{
	m_VertexBuffer->Release();
}

auto Engine::IRenderable::GetVertexBuffer() -> const Scope<VertexBuffer>&
{
	return m_VertexBuffer;
}

auto Engine::IRenderable::Release() const -> void
{
	m_VertexBuffer->Release();
}
