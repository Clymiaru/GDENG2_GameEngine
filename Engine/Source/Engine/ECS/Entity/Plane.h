#pragma once

#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Plane final : public Entity
	{
	public:
		explicit Plane(EntityID id,
					  StringView name,
					  ComponentRegistry* componentRegistry);

		~Plane() override;
	};
}