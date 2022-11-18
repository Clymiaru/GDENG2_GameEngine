#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Cube final : public Entity
	{
	public:
		explicit Cube(EntityID id,
		              StringView name,
		              ComponentRegistry* componentRegistry);

		~Cube() override;
	};
}
