#pragma once
#include <d3d11.h>

namespace Engine
{
	enum class PrimitiveType
	{
		None,
		Cube,
		Plane,
		Sphere,
		Capsule,
		Mesh
	};
	struct RenderData
	{
		// Vertices
		void* Vertices;
		size_t VertexCount;
		size_t VertexSize;

		// Vertex Layout
		D3D11_INPUT_ELEMENT_DESC* VertexLayout;
		size_t VertexLayoutElementCount;

		// Indices
		uint32_t* Indices;
		size_t IndexCount;

		// Topology
		D3D11_PRIMITIVE_TOPOLOGY Topology;

		PrimitiveType PrimitiveType;
	};
}
