#pragma once
#include "Engine/ECS/Component/CameraComponent.h"
#include "Engine/ECS/Component/EditorCameraComponent.h"

namespace Engine
{
	class RenderSystem final
	{
	public:
		RenderSystem() = default;
		~RenderSystem() = default;
		
		void Render(CameraComponent& camera) const;

		void Render(EditorCameraComponent& camera) const;

	};
}

