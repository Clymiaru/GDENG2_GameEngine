#pragma once
#include "../../../../Dependencies/tinyobj/tiny_obj_loader.h"

#include "Engine/Graphics/RenderData.h"
#include <fstream>
#include <sstream>

namespace Engine::Primitive
{
	//TODO: Add normals
	struct Vertex
	{
		Vector3Float Position;
		Vector2Float UV;
		Vector3Float Normal;
	};

	inline RenderData* Mesh(StringView filepath)
	{
		std::ifstream file = std::ifstream(filepath.data());

		std::string fileOutput;
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				fileOutput += line;
			}
			file.close();
		}
		else
		{
			return nullptr;
		}

		tinyobj::attrib_t attributes;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warning;
		std::string error;

		std::string cFilepath = filepath.data();
		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, cFilepath.c_str()))
		{
			Debug::Log("File cannot be loaded! {0}", filepath.data());
			return nullptr;
		}

		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		uint32_t currentIndex = 0;
		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				Vertex vertex;
				vertex.Position.x = attributes.vertices[3 * index.vertex_index + 0];
				vertex.Position.y = attributes.vertices[3 * index.vertex_index + 1];
				vertex.Position.z = attributes.vertices[3 * index.vertex_index + 2];

				vertex.UV.x = attributes.texcoords[2 * index.texcoord_index + 0];
				vertex.UV.y = 1.0f - attributes.texcoords[2 * index.texcoord_index + 1];
				vertices->push_back(vertex);

				indices->push_back(currentIndex);
				currentIndex++;
			}
		}

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* meshRenderData               = new RenderData();
		meshRenderData->Vertices                 = vertices->data();
		meshRenderData->VertexCount              = vertices->size();
		meshRenderData->VertexSize               = sizeof(Vertex);
		meshRenderData->VertexLayout             = layout->data();
		meshRenderData->VertexLayoutElementCount = layout->size();
		meshRenderData->Indices                  = indices->data();
		meshRenderData->IndexCount               = indices->size();
		meshRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return meshRenderData;
	}

	inline RenderData* Cube()
	{
		const Vector3Float basisVector = Vector3Float(0.5f, 0.5f, 0.5f);

		const Vector3Float positionList[] =
		{
			{Vector3Float(-basisVector.x, -basisVector.y, -basisVector.z)},
			{Vector3Float(-basisVector.x, basisVector.y, -basisVector.z)},
			{Vector3Float(basisVector.x, basisVector.y, -basisVector.z)},
			{Vector3Float(basisVector.x, -basisVector.y, -basisVector.z)},

			//BACK FACE
			{Vector3Float(basisVector.x, -basisVector.y, basisVector.z)},
			{Vector3Float(basisVector.x, basisVector.y, basisVector.z)},
			{Vector3Float(-basisVector.x, basisVector.y, basisVector.z)},
			{Vector3Float(-basisVector.x, -basisVector.y, basisVector.z)}
		};

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		const Vector3Float normalList[] =
		{
			Vector3Float::Up,
			Vector3Float::Down,
			Vector3Float::Forward,
			Vector3Float::Backward,
			Vector3Float::Left,
			Vector3Float::Right
		};

		List<Vertex>* vertices = new List<Vertex>{
			{positionList[0], uvList[1], normalList[1]},
			{positionList[1], uvList[0], normalList[1]},
			{positionList[2], uvList[2], normalList[1]},
			{positionList[3], uvList[3], normalList[1]},

			{positionList[4], uvList[1], normalList[4]},
			{positionList[5], uvList[0], normalList[4]},
			{positionList[6], uvList[2], normalList[4]},
			{positionList[7], uvList[3], normalList[4]},

			{positionList[1], uvList[1], normalList[2]},
			{positionList[6], uvList[0], normalList[2]},
			{positionList[5], uvList[2], normalList[2]},
			{positionList[2], uvList[3], normalList[2]},

			{positionList[7], uvList[1], normalList[3]},
			{positionList[0], uvList[0], normalList[3]},
			{positionList[3], uvList[2], normalList[3]},
			{positionList[4], uvList[3], normalList[3]},

			{positionList[3], uvList[1], normalList[5]},
			{positionList[2], uvList[0], normalList[5]},
			{positionList[5], uvList[2], normalList[5]},
			{positionList[4], uvList[3], normalList[5]},

			{positionList[7], uvList[1], normalList[0]},
			{positionList[6], uvList[0], normalList[0]},
			{positionList[1], uvList[2], normalList[0]},
			{positionList[0], uvList[3], normalList[0]}
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		List<uint32_t>* indices = new List<uint32_t>{
			//FRONT SIDE
			0, 1, 2,
			2, 3, 0,
			//BACK SIDE
			4, 5, 6,
			6, 7, 4,
			//TOP SIDE
			8, 9, 10,
			10, 11, 8,
			//BOTTOM SIDE
			12, 13, 14,
			14, 15, 12,
			//RIGHT SIDE
			16, 17, 18,
			18, 19, 16,
			//LEFT SIDE
			20, 21, 22,
			22, 23, 20
		};

		RenderData* cubeRenderData               = new RenderData();
		cubeRenderData->Vertices                 = vertices->data();
		cubeRenderData->VertexCount              = vertices->size();
		cubeRenderData->VertexSize               = sizeof(Vertex);
		cubeRenderData->VertexLayout             = layout->data();
		cubeRenderData->VertexLayoutElementCount = layout->size();
		cubeRenderData->Indices                  = indices->data();
		cubeRenderData->IndexCount               = indices->size();
		cubeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cubeRenderData;
	}

	inline RenderData* Plane()
	{
		const Vector3Float positionList[] =
		{
			{Vector3Float{-0.5f, 0, 0.5f}},
			{Vector3Float{-0.5f, 0, -0.5f}},
			{Vector3Float{0.5f, 0.0f, 0.5f}},
			{Vector3Float{0.5f, 0.0f, -0.5f}}
		};

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)}, // Top Left
			{Vector2Float(0.0f, 1.0f)}, // Bottom Left
			{Vector2Float(1.0f, 0.0f)}, // Top Right
			{Vector2Float(1.0f, 1.0f)} // Botton Right
		};

		List<Vertex>* vertices = new List<Vertex>{
			{positionList[0], uvList[0], Vector3Float::Up},
			{positionList[1], uvList[1], Vector3Float::Up},
			{positionList[2], uvList[2], Vector3Float::Up},
			{positionList[3], uvList[3], Vector3Float::Up},
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		List<uint32_t>* indices = new List<uint32_t>{
			0, 2, 3,
			3, 1, 0
		};

		RenderData* planeRenderData               = new RenderData();
		planeRenderData->Vertices                 = vertices->data();
		planeRenderData->VertexCount              = vertices->size();
		planeRenderData->VertexSize               = sizeof(Vertex);
		planeRenderData->VertexLayout             = layout->data();
		planeRenderData->VertexLayoutElementCount = layout->size();
		planeRenderData->Indices                  = indices->data();
		planeRenderData->IndexCount               = indices->size();
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return planeRenderData;
	}

	// Repurposed Code from: http://www.songho.ca/opengl/gl_sphere.html
	// Sphere
	inline RenderData* Sphere(const uint32_t subdivisions)
	{
		List<Vector3Float> positionList = List<Vector3Float>();
		List<Vector2Float> uvList       = List<Vector2Float>();
		List<Vector3Float> normalList   = List<Vector3Float>();

		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		constexpr float radius = 1.0f;

		constexpr float lengthInv = 1.0f / radius; // normal

		const float sectorStep = 2.0f * PI / (float)subdivisions;
		const float stackStep  = PI / (float)subdivisions;

		for (int i = 0; i <= subdivisions; ++i)
		{
			const float stackAngle = PI / 2.0f - (float)i * stackStep; // starting from pi/2 to -pi/2
			const float xy         = radius * std::cosf(stackAngle); // r * cos(u)
			const float z          = radius * std::sinf(stackAngle); // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= subdivisions; ++j)
			{
				const float sectorAngle = (float)j * sectorStep; // starting from 0 to 2pi

				// vertex position
				const float x = xy * std::cosf(sectorAngle); // r * cos(u) * cos(v)
				const float y = xy * std::sinf(sectorAngle); // r * cos(u) * sin(v)

				const Vector3Float position = Vector3Float{x, y, z};

				// normalized vertex normal
				const float nx = x * lengthInv;
				const float ny = y * lengthInv;
				const float nz = z * lengthInv;

				const Vector3Float normal = Vector3Float{nx, ny, nz};

				// vertex tex coord between [0, 1]
				const float s = (float)j / (float)subdivisions;
				const float t = (float)i / (float)subdivisions;

				const Vector2Float uv = Vector2Float{s, t};

				vertices->push_back(Vertex{position, uv, normal});
			}
		}

		for (int i = 0; i < subdivisions; ++i)
		{
			unsigned int k1 = i * (subdivisions + 1); // beginning of current stack
			unsigned int k2 = k1 + subdivisions + 1; // beginning of next stack

			for (int j = 0; j < subdivisions; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if (i != 0)
				{
					indices->push_back(k1);
					indices->push_back(k2);
					indices->push_back(k1 + 1);
				}

				if (i != (subdivisions - 1))
				{
					indices->push_back(k1 + 1);
					indices->push_back(k2);
					indices->push_back(k2 + 1);
				}
			}
		}

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* sphereRenderData               = new RenderData();
		sphereRenderData->Vertices                 = vertices->data();
		sphereRenderData->VertexCount              = vertices->size();
		sphereRenderData->VertexSize               = sizeof(Vertex);
		sphereRenderData->VertexLayout             = layout->data();
		sphereRenderData->VertexLayoutElementCount = layout->size();
		sphereRenderData->Indices                  = indices->data();
		sphereRenderData->IndexCount               = indices->size();
		sphereRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return sphereRenderData;
	}

	// Capsule
	inline RenderData* Capsule(Vector3Float dimensions, int sectors, int meridians, float equatorialHeight)
	{
		List<Vector3Float> positionList = List<Vector3Float>();
		List<Vector2Float> uvList       = List<Vector2Float>();
		List<Vector3Float> normalList   = List<Vector3Float>();

		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		// TODO: Capsule vertices and indices generation

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
				{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

		RenderData* capsuleRenderData               = new RenderData();
		capsuleRenderData->Vertices                 = vertices->data();
		capsuleRenderData->VertexCount              = vertices->size();
		capsuleRenderData->VertexSize               = sizeof(Vertex);
		capsuleRenderData->VertexLayout             = layout->data();
		capsuleRenderData->VertexLayoutElementCount = layout->size();
		capsuleRenderData->Indices                  = indices->data();
		capsuleRenderData->IndexCount               = indices->size();
		capsuleRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return capsuleRenderData;
	}
	
	struct FrustrumVertex
	{
		Vector3Float Position;
		Vector2Float UV;
	};

	inline RenderData* Frustum(float fov, float windowHeight, float windowLength, float nearZ, float farZ)
	{
		float fovRadians  = fov / 180.0f * 3.14f;
		float aspectRatio = ((float)windowLength / 2.0f) / ((float)windowHeight / 2.0f);

		float nearHeight = 2.0f * std::tan(fovRadians / 2.0f) * nearZ;
		float farHeight  = 2.0f * std::tan(fovRadians / 2.0f) * farZ;
		float nearWidth  = (nearHeight * aspectRatio);
		float farWidth   = (farHeight * aspectRatio);

		float alpha = 0.5f;

		const Vector2Float uvList[] =
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		List<FrustrumVertex>* vertices = new List<FrustrumVertex>{
			{Vector3Float((-nearWidth * 0.5f), (nearHeight * 0.5f), nearZ * 6.0f), uvList[1]},
			{Vector3Float((nearWidth * 0.5f), (nearHeight * 0.5f), nearZ * 6.0f), uvList[0]},
			{Vector3Float((nearWidth * 0.5f), (-nearHeight * 0.5f), nearZ * 6.0f), uvList[2]},
			{Vector3Float(-(nearWidth * 0.5f), (-nearHeight * 0.5f), nearZ * 6.0f), uvList[3]},
			{Vector3Float((-farWidth * 0.5f), (farHeight * 0.5f), farZ * 6.0f), uvList[1]},
			{Vector3Float((farWidth * 0.5f), (farHeight * 0.5f), farZ * 6.0f), uvList[0]},
			{Vector3Float((farWidth * 0.5f), (-farHeight * 0.5f), farZ * 6.0f), uvList[2]},
			{Vector3Float(-(farWidth * 0.5f), (-farHeight * 0.5f), farZ * 6.0f), uvList[3]}
		};

		List<D3D11_INPUT_ELEMENT_DESC>* layout = new List<D3D11_INPUT_ELEMENT_DESC>{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		List<uint32_t>* indices = new List<uint32_t>{
			//Near Plane
			0, 1, 2,
			0, 2, 3,
			//Far Plane
			4, 5, 6,
			4, 6, 7,
			//Left Plane
			0, 4, 7,
			0, 7, 3,
			//Right Plane
			1, 5, 6,
			1, 6, 2,
			//Top Plane
			0, 1, 4,
			1, 4, 5,
			//Bottom Plane
			2, 3, 6,
			3, 6, 7,
		};

		RenderData* frustumRenderData               = new RenderData();
		frustumRenderData->Vertices                 = vertices->data();
		frustumRenderData->VertexCount              = vertices->size();
		frustumRenderData->VertexSize               = sizeof(FrustrumVertex);
		frustumRenderData->VertexLayout             = layout->data();
		frustumRenderData->VertexLayoutElementCount = layout->size();
		frustumRenderData->Indices                  = indices->data();
		frustumRenderData->IndexCount               = indices->size();
		frustumRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

		return frustumRenderData;
	}
}
