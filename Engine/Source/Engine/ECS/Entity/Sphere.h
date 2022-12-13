#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Sphere final : public Entity
	{
	public:
		explicit Sphere(EntityID id,
					  StringView name,
					  ComponentRegistry* componentRegistry);

		~Sphere() override;
	};
}
