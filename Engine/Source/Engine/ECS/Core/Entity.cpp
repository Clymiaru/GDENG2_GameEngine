#include "pch.h"
#include "Entity.h"

namespace Engine
{
	Entity::Entity(const EntityID id,
	               const StringView name,
	               ComponentRegistry* componentRegistry) :
		Active{true},
		m_ID{id},
		m_Name{name.data()},
		m_ComponentRegistry{componentRegistry} { }

	Entity::~Entity() = default;

	EntityID Entity::GetID() const
	{
		return m_ID;
	}

	const String& Entity::GetName() const
	{
		return m_Name;
	}

	// Entity::Entity(const Entity& other) {}
	// Entity& Entity::operator=(const Entity& other) {}
	// Entity::Entity(Entity&& other) noexcept {}
	// Entity& Entity::operator=(Entity&& other) noexcept {}
}
