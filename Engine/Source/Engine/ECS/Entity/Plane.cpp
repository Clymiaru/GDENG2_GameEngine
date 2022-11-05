#include "pch.h"
#include "Plane.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/Graphics/ShaderLibrary.h"

struct PlaneVertex
{
	Engine::Vector3Float Position;
};

namespace Engine
{
	Plane::Plane(const StringView name) :
		Entity(name)
	{
		PlaneVertex* vertices = new PlaneVertex[4]
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
		planeRenderData->VertexSize               = sizeof(PlaneVertex);
		planeRenderData->VertexLayout             = layout;
		planeRenderData->VertexLayoutElementCount = 1U;
		planeRenderData->Indices                  = indices;
		planeRenderData->IndexCount               = sizeof(indices);
		planeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");

		auto vertexShader = ShaderLibrary::GetShaderRef<VertexShader>("SolidColorShader");
		auto pixelShader  = ShaderLibrary::GetShaderRef<PixelShader>("SolidColorShader");

		AttachComponent<RenderComponent>(*this, planeRenderData, vertexShader, pixelShader);
	}

	// TODO: Might need to do some other way if this is a performance bottleneck
	void Plane::Draw(Camera& camera)
	{
		if (RenderComponent* component = GetComponent<RenderComponent>();
			component != nullptr)
		{
			component->Draw(camera);
		}
	}

	Plane::~Plane() = default;
}
