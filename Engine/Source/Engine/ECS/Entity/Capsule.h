#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Capsule final : public Entity
	{
	public:
		explicit Capsule(EntityID id,
					  StringView name,
					  ComponentRegistry* componentRegistry);

		~Capsule() override;
	};
}