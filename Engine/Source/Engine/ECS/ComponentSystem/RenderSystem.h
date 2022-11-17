#pragma once
#include "Engine/ECS/Core/EntityRegistry.h"

namespace Engine
{
	class RenderSystem
	{
	public:
		void Render(EntityRegistry& entityRegistry);
	};
}

