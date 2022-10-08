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

	auto RenderObject::GetVertexBuffer() const -> VertexBuffer&
	{
		return *m_VertexBuffer;
	}

	auto RenderObject::GetIndexBuffer() const -> IndexBuffer&
	{
		return *m_IndexBuffer;
	}
}
