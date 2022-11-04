#include "pch.h"
#include "Entity.h"

#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	Entity::Entity(const String& name) :
		m_Name{name},
		m_Transform{nullptr},
		m_ComponentList{}
	{
		m_Transform = new TransformComponent(*this);
	}

	Entity::~Entity()
	{
		delete m_Transform;
	}

	const String& Entity::Name()
	{
		return m_Name;
	}

	TransformComponent& Entity::Transform() const
	{
		return *m_Transform;
	}
}
