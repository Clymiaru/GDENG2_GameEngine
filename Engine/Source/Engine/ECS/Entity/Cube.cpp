#include "pch.h"
#include "Cube.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"
#include "Engine/Graphics/Primitives/Primitive.h"
#include "Engine/ResourceManagement/Core/ResourceSystem.h"

namespace Engine
{
	Cube::Cube(const EntityID id,
	           const StringView name,
	           ComponentRegistry* componentRegistry) :
		Entity{id, name, componentRegistry}
	{
		RenderData* cubeRenderData = Primitive::Cube();

		Application::GetResourceSystem().Load<VertexShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");
		Application::GetResourceSystem().Load<PixelShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");

		AttachComponent<TransformComponent>();

		auto vertexShader = Application::GetResourceSystem().Get<VertexShaderResource>("SolidColorShader");
		auto pixelShader  = Application::GetResourceSystem().Get<PixelShaderResource>("SolidColorShader");
		
		AttachComponent<RenderComponent>(cubeRenderData, vertexShader, pixelShader);
	}

	Cube::~Cube() = default;
}
