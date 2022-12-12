#include "pch.h"
#include "Cube.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/RenderComponent.h"
#include "Engine/ECS/Component/Render/StaticMeshComponent.h"
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

		Application::GetResourceSystem().Load<VertexShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		Application::GetResourceSystem().Load<PixelShader>("Assets/Shaders/Basic/TexturedShader.hlsl");

		auto transform = AttachComponent<TransformComponent>();

		auto vertexShader = Application::GetResourceSystem().Get<VertexShaderResource>("TexturedShader");
		auto pixelShader  = Application::GetResourceSystem().Get<PixelShaderResource>("TexturedShader");
		
		AttachComponent<StaticMeshComponent>(cubeRenderData, vertexShader, pixelShader, transform);
	}

	Cube::~Cube() = default;
}
