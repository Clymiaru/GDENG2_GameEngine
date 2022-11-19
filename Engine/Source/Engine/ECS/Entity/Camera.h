#pragma once
#include "Engine/Math/Math.h"

#include "Engine/ECS/Core/Entity.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	class Camera final : public Entity
	{
	public:
		explicit Camera(EntityID id,
		                StringView name,
		                ComponentRegistry* componentRegistry,
		                uint64_t renderWidth,
		                uint64_t renderHeight);

		~Camera() override;
	};
}
