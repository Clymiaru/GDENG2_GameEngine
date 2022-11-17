#include "pch.h"
#include "Entity.h"

#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	Entity::Entity(const EntityID id) :
		Active{true},
		m_ID{id} { }

	Entity::~Entity() = default;
	
	EntityID Entity::GetID() const
	{
		return m_ID;
	}

	Entity::Entity(const Entity& other) {}
	Entity& Entity::operator=(const Entity& other) {}
	Entity::Entity(Entity&& other) noexcept {}
	Entity& Entity::operator=(Entity&& other) noexcept {}
}
