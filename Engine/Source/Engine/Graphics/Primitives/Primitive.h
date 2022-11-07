#pragma once
#include "Engine/Graphics/RenderData.h"

namespace Engine::Primitive
{
	struct Vertex
	{
		Vector3Float Position;
	};

	inline RenderData* Circle(float radius,
	                          int sectors)
	{
		List<Vertex> vertices = List<Vertex>();
		List<uint32_t> indices = List<uint32_t>();

		int centerN = (int)vertices.size();

		vertices.push_back({
			                   Vector3Float(0.0f, 0.0f, 0.0f)
		                   });

		for (int i = 0; i <= sectors; i++)
		{
			const int n = vertices.size();

			const float angle = (PI * 2 *  (float)i) / (float)sectors;
			Vector3Float sphericalPoint = Vector3Float(0.0f, 0.0f, 0.0f);

			sphericalPoint = Vector3Float (
					std::cos(angle) * radius,
					std::sin(angle) * radius, 0.0f);

			vertices.push_back({sphericalPoint});
			
			if (i > 0)
			{
				indices.push_back(n);
				indices.push_back(n-1);
				indices.push_back(centerN);
			}
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		
		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices.data();
		planeRenderData->VertexCount              = vertices.size();
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices.data();
		planeRenderData->IndexCount               = indices.size();
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	inline RenderData* Cube()
	{
		Vertex* vertices = new Vertex[8]
		{
			{Vector3Float{-0.5f, -0.5f, -0.5f}},
			{Vector3Float{-0.5f, 0.5f, -0.5f}},
			{Vector3Float{0.5f, 0.5f, -0.5f}},
			{Vector3Float{0.5f, -0.5f, -0.5f}},
			{Vector3Float{0.5f, -0.5f, 0.5f}},
			{Vector3Float{0.5f, 0.5f, 0.5f}},
			{Vector3Float{-0.5f, 0.5f, 0.5f}},
			{Vector3Float{-0.5f, -0.5f, 0.5f}}
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[36]
		{
			//FRONT SIDE
			0,
			1,
			2,
			//FIRST TRIANGLE
			2,
			3,
			0,
			//SECOND TRIANGLE
			//BACK SIDE
			4,
			5,
			6,
			6,
			7,
			4,
			//TOP SIDE
			1,
			6,
			5,
			5,
			2,
			1,
			//BOTTOM SIDE
			7,
			0,
			3,
			3,
			4,
			7,
			//RIGHT SIDE
			3,
			2,
			5,
			5,
			4,
			3,
			//LEFT SIDE
			7,
			6,
			1,
			1,
			0,
			7
		};

		RenderData* cubeRenderData               = new RenderData();
		cubeRenderData->Vertices                 = vertices;
		cubeRenderData->VertexCount              = sizeof(*vertices);
		cubeRenderData->VertexSize               = sizeof(Vertex);
		cubeRenderData->VertexLayout             = layout;
		cubeRenderData->VertexLayoutElementCount = 1U;
		cubeRenderData->Indices                  = indices;
		cubeRenderData->IndexCount               = 36;
		cubeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cubeRenderData;
	}

	inline RenderData* Plane()
	{
		Vertex* vertices = new Vertex[4]
		{
			{Vector3Float{-0.5f, 0, -0.5f}},
			{Vector3Float{-0.5f, 0, 0.5f}},
			{Vector3Float{0.5f, 0.0f, 0.5f}},
			{Vector3Float{0.5f, 0.0f, -0.5f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices;
		planeRenderData->VertexCount              = sizeof(*vertices);
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices;
		planeRenderData->IndexCount               = sizeof(indices);
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	// TODO:
	inline RenderData* Capsule()
	{
		Vertex* vertices = new Vertex[4]
		{
			{Vector3Float{-0.5f, 0, -0.5f}},
			{Vector3Float{-0.5f, 0, 0.5f}},
			{Vector3Float{0.5f, 0.0f, 0.5f}},
			{Vector3Float{0.5f, 0.0f, -0.5f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices;
		planeRenderData->VertexCount              = sizeof(*vertices);
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices;
		planeRenderData->IndexCount               = sizeof(indices);
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	// TODO:
	inline RenderData* Cylinder()
	{
		Vertex* vertices = new Vertex[4]
		{
			{Vector3Float{-0.5f, 0, -0.5f}},
			{Vector3Float{-0.5f, 0, 0.5f}},
			{Vector3Float{0.5f, 0.0f, 0.5f}},
			{Vector3Float{0.5f, 0.0f, -0.5f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices;
		planeRenderData->VertexCount              = sizeof(*vertices);
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices;
		planeRenderData->IndexCount               = sizeof(indices);
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	// TODO:
	inline RenderData* Sphere()
	{
		Vertex* vertices = new Vertex[4]
		{
			{Vector3Float{-0.5f, 0, -0.5f}},
			{Vector3Float{-0.5f, 0, 0.5f}},
			{Vector3Float{0.5f, 0.0f, 0.5f}},
			{Vector3Float{0.5f, 0.0f, -0.5f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices;
		planeRenderData->VertexCount              = sizeof(*vertices);
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices;
		planeRenderData->IndexCount               = sizeof(indices);
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}
}
