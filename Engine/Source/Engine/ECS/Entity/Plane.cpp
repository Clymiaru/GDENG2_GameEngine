#include "pch.h"
#include "Plane.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Component/TransformComponent.h"

struct Vertex
{
	Engine::Vector3Float Position;

	Engine::Color Color;
};

namespace Engine
{
	Plane::Plane(const String& name,
	             const Vector3Float& position) :
		Entity(name),
		m_Render{new RenderComponent(this)}
	{
		Transform().Position = position;

		Vertex* vertices = new Vertex[4]
		{
			{
				Vector3Float{-0.5f, 0, -0.5f},
				Color{0.0f, 0, 0.8f}
			},

			{
				Vector3Float{-0.5f, 0, 0.5f},
				Color{0.0f, 0.8f, 0.8f}
			},

			{
				Vector3Float{0.5f, 0.0f, 0.5f},
				Color{0.0f, 0.8f, 0.8f}
			},

			{
				Vector3Float{0.5f, 0.0f, -0.5f},
				Color{0.0f, 0, 0.8f},
			},
		};

		size_t vertexSize = sizeof(*vertices);

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		uint32_t* indices = new uint32_t[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};
		//size_t indexSize = ARRAYSIZE(indices);

		m_Render->Initialize(new RenderComponent::VertexData{vertices, vertexSize},
		                     new RenderComponent::VertexLayoutData{layout, layoutSize},
		                     new RenderComponent::IndexData{indices, 36},
		                     sizeof(Vertex),
		                     "DefaultShader");
	}

	void Plane::Update()
	{
		m_Render->Update();
	}

	void Plane::Draw(Camera& camera)
	{
		m_Render->Draw(camera);
	}

	Plane::~Plane()
	{
		delete m_Render;
	}
}
