#include "pch.h"
#include "Quad.h"
#include <Windows.h>
#include "Engine/Graphics/Vertex.h"

namespace Engine
{
	struct QuadVertex
	{
		Vector3Float Position;

		Vector3Float Size;

		Color32 Color;
	};

	Quad::Quad(const Vector2Float& position,
	           const Vector2Float& size,
	           const Color32& color):
		m_Position{position},
		m_Size{size},
		m_Color{color},
		m_Vertices{nullptr},
		m_VerticesSize{0}
	{
		float animValue = 0.01f;
		auto vertices   = new QuadVertex[6]
		{
			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f - animValue, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f - animValue, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f - animValue, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f - animValue, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f - animValue, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			},

			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f - animValue, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			}
		};

		m_Vertices     = vertices;
		m_VerticesSize = 6;
	}

	Quad::~Quad()
	{
	}

	auto Quad::GetListOfVertices() -> void*
	{
		return m_Vertices;
	}

	auto Quad::GetListOfVerticesSize() -> size_t
	{
		return m_VerticesSize;
	}

	auto Quad::GetVertexSize() -> size_t
	{
		return sizeof(QuadVertex);
	}

	auto Quad::GetIndexLayoutAndSize() -> IndexLayoutInfo&
	{
		return *m_IndexLayout;
	}

	auto Quad::SetIndexLayoutAndSize(IndexLayoutInfo indexLayoutInfo) -> void
	{
		m_IndexLayout = CreateUniquePtr<IndexLayoutInfo>(indexLayoutInfo);
	}
}
