#include "pch.h"
#include "Cube.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"

struct Vertex
{
	Engine::Vector3Float Position;

	Engine::Color Color;
};

namespace Engine
{
	Cube::Cube(const String& name,
	           const Vector3Float& position) :
		Entity{name},
		m_Render{new RenderComponent(*this)}
	{
		Transform().Position = position;

		Vertex* vertices = new Vertex[8]
		{
			{
				Vector3Float{-0.5f, -0.5f, -0.5f},
				Color{0.8f, 0, 0}
			},

			{
				Vector3Float{-0.5f, 0.5f, -0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3Float{0.5f, 0.5f, -0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3Float{0.5f, -0.5f, -0.5f},
				Color{0.8f, 0, 0},
			},

			{
				Vector3Float{0.5f, -0.5f, 0.5f},
				Color{0, 0.8f, 0}
			},

			{
				Vector3Float{0.5f, 0.5f, 0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3Float{-0.5f, 0.5f, 0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3Float{-0.5f, -0.5f, 0.5f},
				Color{0, 0.8f, 0},
			}
		};

		size_t vertexSize = sizeof(*vertices);

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

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
		//size_t indexSize = ARRAYSIZE(indices);

		m_Render->Initialize(new RenderComponent::VertexData{vertices, vertexSize},
		                     new RenderComponent::VertexLayoutData{layout, layoutSize},
		                     new RenderComponent::IndexData{indices, 36},
		                     sizeof(Vertex),
		                     "DefaultShader");
	}

	Cube::~Cube()
	{
		delete m_Render;
	}

	void Cube::Update()
	{
		m_Render->Update();
	}

	// void Cube::Update(float deltaTime)
	// {
	// 	using namespace DirectX;
	//
	// 	m_Constant->Time = deltaTime;
	//
	// 	m_Constant->Model = Transform();
	//
	// 	// To be transferred to camera later
	// 	m_Constant->View = Camera::Instance().ViewProjMatrix();
	// 	//m_Constant->View = XMMatrixTranspose(m_Constant->View);
	//
	// 	m_Constant->Projection = XMMatrixIdentity();
	// }

	void Cube::Draw(Camera& camera)
	{
		m_Render->Draw(camera);
	}
}
