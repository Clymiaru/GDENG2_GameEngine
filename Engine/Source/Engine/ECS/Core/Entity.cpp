#include "pch.h"
#include "Entity.h"

#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	Entity::Entity(const StringView name) :
		Name{name.data()},
		m_ComponentTable{HashMap<String, AComponent*>()},
		m_Transform{nullptr}
	{
		m_Transform = new TransformComponent(*this);
	}

	Entity::~Entity()
	{
		m_ComponentTable.clear();
		delete m_Transform;
	}

	TransformComponent& Entity::Transform() const
	{
		return *m_Transform;
	}
}
