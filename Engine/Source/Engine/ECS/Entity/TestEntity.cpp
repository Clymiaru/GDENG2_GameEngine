#include "pch.h"
#include "TestEntity.h"

#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	TestEntity::TestEntity(const EntityID id,
	                       const StringView name,
	                       ComponentRegistry* componentRegistry) :
		Entity{id, name, componentRegistry}
	{
		AttachComponent<TransformComponent>();
	}

	TestEntity::~TestEntity() {}
}
