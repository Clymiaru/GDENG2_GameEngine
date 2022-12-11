#include "pch.h"
#include "EditorCamera.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"

#include "Engine/Core/Application.h"

namespace Engine
{
	EditorCamera::EditorCamera(const EntityID id,
	                           const StringView name,
	                           ComponentRegistry* componentRegistry,
	                           uint64_t renderWidth,
	                           uint64_t renderHeight) :
		Entity{id, name, componentRegistry}
	{
		auto transform = AttachComponent<TransformComponent>();
		transform->Position.y = 20.0f;
		transform->Position.z = -5.0f;
		transform->Rotation.x = 90.0f;
		
		AttachComponent<EditorCameraComponent>(transform, renderWidth, renderHeight);
	}

	EditorCamera::~EditorCamera() = default;
}
