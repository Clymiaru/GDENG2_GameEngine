#include "pch.h"
#include "RenderObject.h"

namespace Engine
{
	RenderObject::RenderObject() :
		m_VertexData{},
		m_VertexLayoutData{},
		m_IndexData{},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr}
	{
	}

	RenderObject::~RenderObject() = default;

	VertexBuffer& RenderObject::GetVertexBuffer() const
	{
		return *m_VertexBuffer;
	}

	IndexBuffer& RenderObject::GetIndexBuffer() const
	{
		return *m_IndexBuffer;
	}
}
