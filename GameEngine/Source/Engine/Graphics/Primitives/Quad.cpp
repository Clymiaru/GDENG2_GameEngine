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
		auto vertices   = new QuadVertex[6]
		{
			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f, m_Position.Y + m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			},

			{
				Vector3Float{m_Position.X + m_Size.X / 2.0f, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			},

			{
				Vector3Float{m_Position.X - m_Size.X / 2.0f, m_Position.Y - m_Size.Y / 2.0f, 0.0f},
				Vector3Float{m_Size.X, m_Size.Y, 1.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			}
		};

		m_Vertices     = vertices;
		m_VerticesSize = 6;



		auto* layout = new D3D11_INPUT_ELEMENT_DESC[3]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"SIZE", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		auto layoutSize = 3U;
		SetIndexLayoutAndSize({ layout, layoutSize });
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
	auto Quad::GetTransform() -> DirectX::XMMATRIX&
	{
		return m_ModelMat;
	}
	auto Quad::GetConstantBuffer() -> ConstantBuffer*
	{
		return m_ConstantBuffer;
	}
	auto Quad::SetConstantBuffer(ConstantBuffer* constantBuffer) -> void
	{
		m_ConstantBuffer = std::move(constantBuffer);
	}
}
