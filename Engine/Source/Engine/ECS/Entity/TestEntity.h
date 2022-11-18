#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class TestEntity final : public Entity
	{
	public:
		explicit TestEntity(EntityID id, StringView name, ComponentRegistry* componentRegistry);
		~TestEntity() override;
	};
}

