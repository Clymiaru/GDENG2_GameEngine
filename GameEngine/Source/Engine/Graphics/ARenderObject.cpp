#include "pch.h"
#include "ARenderObject.h"

namespace Engine
{
	ARenderObject::ARenderObject() :
		m_VertexData{},
		m_VertexLayoutData{},
		m_IndexData{},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr}
	{
	}

	ARenderObject::~ARenderObject() = default;

	auto ARenderObject::GetVertexBuffer() const -> const UniquePtr<VertexBuffer>&
	{
		return m_VertexBuffer;
	}

	auto ARenderObject::GetIndexBuffer() const -> const UniquePtr<IndexBuffer>&
	{
		return m_IndexBuffer;
	}
}
