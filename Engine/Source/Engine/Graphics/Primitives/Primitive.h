#pragma once
#include "Engine/Graphics/RenderData.h"

namespace Engine::Primitive
{
	struct Vertex
	{
		Vector3Float Position;
	};

	struct TexturedVertex
	{
		Vector3Float Position;

		Vector2Float TextureCoordinates;
	};

	inline RenderData* Circle(const int sectors)
	{
		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		constexpr int centerIndex = 0;

		vertices->push_back({Vector3Float()});

		for (int i = 0; i <= sectors; i++)
		{
			const int n = (int)vertices->size();

			const float angle = (PI * 2 * (float)i) / (float)sectors;

			vertices->push_back({Vector3Float(std::cos(angle), std::sin(angle), 0.0f)});

			if (i > 0)
			{
				indices->push_back(n);
				indices->push_back(n - 1);
				indices->push_back(centerIndex);
			}
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* circleRenderData               = new RenderData();
		circleRenderData->Vertices                 = vertices->data();
		circleRenderData->VertexCount              = vertices->size();
		circleRenderData->VertexSize               = sizeof(Vertex);
		circleRenderData->VertexLayout             = layout;
		circleRenderData->VertexLayoutElementCount = 1U;
		circleRenderData->Indices                  = indices->data();
		circleRenderData->IndexCount               = indices->size();
		circleRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return circleRenderData;
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

	inline RenderData* RainbowCube()
	{
		Vector3Float* positionList = new Vector3Float[]
		{
			{Vector3Float(-0.5f, -0.5f, -0.5f)},
			{Vector3Float(-0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, -0.5f, -0.5f)},

			//BACK FACE
			{Vector3Float(0.5f, -0.5f, 0.5f)},
			{Vector3Float(0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, -0.5f, 0.5f)}
		};

		Vector2Float* texCoordList = new Vector2Float[]
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		TexturedVertex* vertexList = new TexturedVertex[]
		{
			{positionList[0], texCoordList[1]},
			{positionList[1], texCoordList[0]},
			{positionList[2], texCoordList[2]},
			{positionList[3], texCoordList[3]},

			{positionList[4], texCoordList[1]},
			{positionList[5], texCoordList[0]},
			{positionList[6], texCoordList[2]},
			{positionList[7], texCoordList[3]},

			{positionList[1], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[2], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[0], texCoordList[0]},
			{positionList[3], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[3], texCoordList[1]},
			{positionList[2], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[1], texCoordList[2]},
			{positionList[0], texCoordList[3]}

		};

		uint32_t* indexList  = new uint32_t[]
		{
			//FRONT SIDE
			0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* cubeRenderData               = new RenderData();
		cubeRenderData->Vertices                 = vertexList;
		cubeRenderData->VertexCount              = sizeof(*vertexList);
		cubeRenderData->VertexSize               = sizeof(TexturedVertex);
		cubeRenderData->VertexLayout             = layout;
		cubeRenderData->VertexLayoutElementCount = 2U;
		cubeRenderData->Indices                  = indexList;
		cubeRenderData->IndexCount               = 36;
		cubeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cubeRenderData;
	}

	inline RenderData* TexturedCube()
	{
		Vector3Float* positionList = new Vector3Float[]
		{
			{Vector3Float(-0.5f, -0.5f, -0.5f)},
			{Vector3Float(-0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, 0.5f, -0.5f)},
			{Vector3Float(0.5f, -0.5f, -0.5f)},

			//BACK FACE
			{Vector3Float(0.5f, -0.5f, 0.5f)},
			{Vector3Float(0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, 0.5f, 0.5f)},
			{Vector3Float(-0.5f, -0.5f, 0.5f)}
		};

		Vector2Float* texCoordList = new Vector2Float[]
		{
			{Vector2Float(0.0f, 0.0f)},
			{Vector2Float(0.0f, 1.0f)},
			{Vector2Float(1.0f, 0.0f)},
			{Vector2Float(1.0f, 1.0f)}
		};

		TexturedVertex* vertexList = new TexturedVertex[]
		{
			{positionList[0], texCoordList[1]},
			{positionList[1], texCoordList[0]},
			{positionList[2], texCoordList[2]},
			{positionList[3], texCoordList[3]},

			{positionList[4], texCoordList[1]},
			{positionList[5], texCoordList[0]},
			{positionList[6], texCoordList[2]},
			{positionList[7], texCoordList[3]},

			{positionList[1], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[2], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[0], texCoordList[0]},
			{positionList[3], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[3], texCoordList[1]},
			{positionList[2], texCoordList[0]},
			{positionList[5], texCoordList[2]},
			{positionList[4], texCoordList[3]},

			{positionList[7], texCoordList[1]},
			{positionList[6], texCoordList[0]},
			{positionList[1], texCoordList[2]},
			{positionList[0], texCoordList[3]}

		};

		unsigned int indexList[] =
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
			8,
			9,
			10,
			10,
			11,
			8,
			//BOTTOM SIDE
			12,
			13,
			14,
			14,
			15,
			12,
			//RIGHT SIDE
			16,
			17,
			18,
			18,
			19,
			16,
			//LEFT SIDE
			20,
			21,
			22,
			22,
			23,
			20
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* cubeRenderData               = new RenderData();
		cubeRenderData->Vertices                 = vertexList;
		cubeRenderData->VertexCount              = sizeof(*vertexList);
		cubeRenderData->VertexSize               = sizeof(TexturedVertex);
		cubeRenderData->VertexLayout             = layout;
		cubeRenderData->VertexLayoutElementCount = 2U;
		cubeRenderData->Indices                  = indexList;
		cubeRenderData->IndexCount               = sizeof(*indexList);
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

	inline RenderData* Capsule(const int sectors,
	                           const int meridians,
	                           const float equatorialHeight)
	{
		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		const int equatorialMeridian = meridians / 2;

		for (int i = 0; i <= sectors; i++)
		{
			float longitude = (PI * 2 * (float)i) / (float)sectors;

			float verticalOffset = -equatorialHeight / 2;

			// This sequences multiple times through on the equatorial meridian:
			//	- the last band of verts on the lower hemisphere
			//	- the bottom band of verts on the equator
			//	- the top band of verts on the equator
			//	- finally to continue to draw the first band of verts on the upper hemisphere

			constexpr int extraMeridians = 4;

			int createEquator = extraMeridians - 1;

			// total V distance along the curved portion (upper and lower hemispheres combined)
			// see note about elliptical distance: this distorts with non-uniform dimensions.
			float curvedVDistance = PI;

			for (int j = 0; j <= meridians; j++)
			{
				bool emitTriangles = true;

				const int effectiveJ = j;

				if (j == equatorialMeridian)
				{
					if (createEquator > 0)
					{
						// last (topmost) band of verts on lower hemisphere
						if (createEquator == 3)
						{
						}
						// bottom band of verts on the equator band
						if (createEquator == 2)
						{
							// don't want these zero-height polys as we transition
							// from the lower hemisphere to the equatorial band.
							emitTriangles = false;
						}
						// top band of verts on the equator band
						if (createEquator == 1)
						{
							verticalOffset = -verticalOffset;
						}

						createEquator--;

						j--;
					}
					else
					{
						// don't want these zero-height polys as we transition
						// from the equatorial band to the upper hemisphere
						emitTriangles = false;
					}
				}

				int n = vertices->size();

				const float latitude = ((float)effectiveJ * PI) / (float)meridians - PI / 2;

				const Vector3Float sphericalPoint = Vector3Float(std::cos(longitude) * std::cos(latitude),
				                                                 std::sin(latitude) + verticalOffset,
				                                                 std::sin(longitude) * std::cos(latitude));

				vertices->push_back({sphericalPoint});

				if (emitTriangles)
				{
					if (i > 0 && j > 0)
					{
						const int effectiveMeridians = meridians + extraMeridians;

						indices->push_back(n);
						indices->push_back(n - effectiveMeridians - 1);
						indices->push_back(n - effectiveMeridians);

						indices->push_back(n);
						indices->push_back(n - 1);
						indices->push_back(n - effectiveMeridians - 1);
					}
				}
			}
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* cylinderRenderData               = new RenderData();
		cylinderRenderData->Vertices                 = vertices->data();
		cylinderRenderData->VertexCount              = vertices->size();
		cylinderRenderData->VertexSize               = sizeof(Vertex);
		cylinderRenderData->VertexLayout             = layout;
		cylinderRenderData->VertexLayoutElementCount = 1U;
		cylinderRenderData->Indices                  = indices->data();
		cylinderRenderData->IndexCount               = indices->size();
		cylinderRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cylinderRenderData;
	}

	// TODO:
	inline RenderData* Cylinder(int sectors,
	                            int meridians)
	{
		auto getUnitCircleVertices = [sectors]() -> List<float>
		{
			float sectorStep = 2 * PI / sectors;
			float sectorAngle; // radian

			List<float> unitCircleVertices;
			for (int i = 0; i <= sectors; ++i)
			{
				sectorAngle = i * sectorStep;
				unitCircleVertices.push_back(cos(sectorAngle)); // x
				unitCircleVertices.push_back(sin(sectorAngle)); // y
				unitCircleVertices.push_back(0); // z
			}
			return unitCircleVertices;
		};

		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		List<float> unitVertices = getUnitCircleVertices();

		for (int i = 0; i < 2; ++i)
		{
			float h = -1.0 / 2.0f + i * 1.0; // z value; -h/2 to h/2
			float t = 1.0f - i; // vertical tex coord; 1 to 0

			for (int j = 0, k = 0; j <= sectors; ++j, k += 3)
			{
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];
				float uz = unitVertices[k + 2];
				// position vector
				vertices->push_back({Vector3Float{ux * 1.0f, uy * 1.0f, h}}); // vx
			}
		}

		int baseCenterIndex = (int)vertices->size() / 3;
		int topCenterIndex  = baseCenterIndex + sectors + 1; // include center vertex

		// put base and top vertices to arrays
		for (int i = 0; i < 2; ++i)
		{
			float h  = -1.0f / 2.0f + (float)i * 1.0f; // z value; -h/2 to h/2
			float nz = -1.0f + (float)i * 2; // z value of normal; -1 to 1

			// center point
			Vector3Float centerPoint = Vector3Float();
			vertices->push_back({centerPoint});

			for (int j = 0, k = 0; j < sectors; ++j, k += 3)
			{
				float ux = unitVertices[k];
				float uy = unitVertices[k + 1];

				vertices->push_back({Vector3Float{ux * 1.0f, uy * 1.0f, h}});
			}
		}

		int k1 = 0; // 1st vertex index at base
		int k2 = sectors + 1; // 1st vertex index at top

		// indices for the side surface
		for (int i = 0; i < sectors; ++i, ++k1, ++k2)
		{
			// 2 triangles per sector
			// k1 => k1+1 => k2
			indices->push_back(k1);
			indices->push_back(k1 + 1);
			indices->push_back(k2);

			// k2 => k1+1 => k2+1
			indices->push_back(k2);
			indices->push_back(k1 + 1);
			indices->push_back(k2 + 1);
		}

		// indices for the base surface
		//NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
		//      please see the previous code snippet
		for (int i = 0, k = baseCenterIndex + 1; i < sectors; i++, k++)
		{
			if (i < sectors - 1)
			{
				indices->push_back(baseCenterIndex);
				indices->push_back(k + 1);
				indices->push_back(k);
			}
			else // last triangle
			{
				indices->push_back(baseCenterIndex);
				indices->push_back(baseCenterIndex + 1);
				indices->push_back(k);
			}
		}

		for (int i = 0, k = topCenterIndex + 1; i < sectors; i++, k++)
		{
			if (i < sectors - 1)
			{
				indices->push_back(topCenterIndex);
				indices->push_back(k);
				indices->push_back(k + 1);
			}
			else // last triangle
			{
				indices->push_back(topCenterIndex);
				indices->push_back(k);
				indices->push_back(topCenterIndex + 1);
			}
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* cylinderRenderData               = new RenderData();
		cylinderRenderData->Vertices                 = vertices->data();
		cylinderRenderData->VertexCount              = vertices->size();
		cylinderRenderData->VertexSize               = sizeof(Vertex);
		cylinderRenderData->VertexLayout             = layout;
		cylinderRenderData->VertexLayoutElementCount = 1U;
		cylinderRenderData->Indices                  = indices->data();
		cylinderRenderData->IndexCount               = indices->size();
		cylinderRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return cylinderRenderData;
	}

	inline RenderData* Sphere(const int subdivisions)
	{
		List<Vertex>* vertices  = new List<Vertex>();
		List<uint32_t>* indices = new List<uint32_t>();

		const int stackCount  = subdivisions;
		const int sectorCount = subdivisions;

		const float sectorStep = 2.0f * PI / (float)sectorCount;
		const float stackStep  = PI / (float)stackCount;

		for (int i = 0; i <= stackCount; i++)
		{
			const float stackAngle = PI / 2.0f - (float)i * stackStep;
			const float xy         = std::cos(stackAngle);
			const float y          = std::sin(stackAngle);

			for (int j = 0; j <= sectorCount; j++)
			{
				const float sectorAngle = j * sectorStep;
				const float z           = xy * std::cos(sectorAngle);
				const float x           = xy * std::sin(sectorAngle);

				vertices->push_back({Vector3Float(x, y, z)});
			}
		}

		for (int i = 0; i < stackCount; i++)
		{
			int k1 = i * (sectorCount + 1);
			int k2 = k1 + sectorCount + 1;

			for (int j = 0; j < sectorCount; j++)
			{
				if (i != 0)
				{
					indices->push_back(k1);
					indices->push_back(k1 + 1);
					indices->push_back(k2);
				}

				if (i != (stackCount - 1))
				{
					indices->push_back(k1 + 1);
					indices->push_back(k2 + 1);
					indices->push_back(k2);
				}

				k1++;
				k2++;
			}
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		RenderData* sphereRenderData               = new RenderData();
		sphereRenderData->Vertices                 = vertices->data();
		sphereRenderData->VertexCount              = vertices->size();
		sphereRenderData->VertexSize               = sizeof(Vertex);
		sphereRenderData->VertexLayout             = layout;
		sphereRenderData->VertexLayoutElementCount = 1U;
		sphereRenderData->Indices                  = indices->data();
		sphereRenderData->IndexCount               = indices->size();
		sphereRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		return sphereRenderData;
	}
}
