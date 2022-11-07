#include "pch.h"
#include "Cube.h"

#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Graphics/Primitives/Primitive.h"

namespace Engine
{
	Cube::Cube(const StringView name) :
		Entity{name}
	{
		RenderData* cubeRenderData = Primitive::Cube();

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
