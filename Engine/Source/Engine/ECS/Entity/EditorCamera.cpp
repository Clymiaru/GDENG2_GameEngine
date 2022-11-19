#include "pch.h"
#include "EditorCamera.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"

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
		AttachComponent<EditorCameraComponent>(transform, renderWidth, renderHeight);
	}

	EditorCamera::~EditorCamera() = default;
}
