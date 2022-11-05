#include "pch.h"
#include "Cube.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/Graphics/ShaderLibrary.h"

struct CubeVertex
{
	Engine::Vector3Float Position;
};

namespace Engine
{
	Cube::Cube(const StringView name) :
		Entity{name}
	{
		CubeVertex* vertices = new CubeVertex[8]
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
		cubeRenderData->VertexSize               = sizeof(CubeVertex);
		cubeRenderData->VertexLayout             = layout;
		cubeRenderData->VertexLayoutElementCount = 1U;
		cubeRenderData->Indices                  = indices;
		cubeRenderData->IndexCount               = 36;
		cubeRenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");

		auto vertexShader = ShaderLibrary::GetShaderRef<VertexShader>("SolidColorShader");
		auto pixelShader  = ShaderLibrary::GetShaderRef<PixelShader>("SolidColorShader");

		AttachComponent<RenderComponent>(*this, cubeRenderData, vertexShader, pixelShader);
	}

	Cube::~Cube() = default;

	// TODO: Might need to do some other way if this is a performance bottleneck
	void Cube::Draw(Camera& camera)
	{
		if (const auto* component = GetComponent<RenderComponent>();
			component != nullptr)
		{
			component->Draw(camera);
		}
	}
}
