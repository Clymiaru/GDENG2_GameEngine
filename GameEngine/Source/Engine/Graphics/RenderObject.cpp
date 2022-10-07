#include "pch.h"
#include "RenderObject.h"
#include "VertexBuffer.h"

Engine::RenderObject::RenderObject()
{
	m_VertexBuffer = CreateUniquePtr<VertexBuffer>();
}

Engine::RenderObject::~RenderObject()
{
}

auto Engine::RenderObject::Load(void* listOfVertices,
                                UINT vertexSize,
                                UINT listSize,
                                void* shaderByteCode,
                                UINT byteShaderSize) -> void
{
	m_VertexBuffer->Load(listOfVertices,
	                     vertexSize,
	                     listSize,
	                     shaderByteCode,
	                     byteShaderSize,
	                     m_IndexLayoutDescription,
	                     m_IndexLayoutDescriptionSize);
}

auto Engine::RenderObject::SetIndexLayout(D3D11_INPUT_ELEMENT_DESC* indexLayout,
                                          size_t indexLayoutSize) -> void
{
	m_IndexLayoutDescription     = indexLayout;
	m_IndexLayoutDescriptionSize = indexLayoutSize;
}
