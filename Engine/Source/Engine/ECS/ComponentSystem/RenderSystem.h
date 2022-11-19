#pragma once
#include "Engine/ECS/Component/CameraComponent.h"

namespace Engine
{
	class RenderSystem final
	{
	public:
		RenderSystem() = default;
		~RenderSystem() = default;
		
		void Render(CameraComponent& camera) const;
	};
}

