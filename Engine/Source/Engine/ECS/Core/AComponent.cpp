#include "pch.h"
#include "AComponent.h"

#include "Entity.h"

namespace Engine
{
	AComponent::AComponent(Entity& owner) :
		m_EntityRef{owner} { }

	AComponent::~AComponent() = default;

	Entity& AComponent::GetOwner() const
	{
		return m_EntityRef;
	}

	bool AComponent::operator==(const AComponent& other) const
	{
		return GetName() == other.GetName() &&
		       m_EntityRef.GetID() == other.GetOwner().GetID();
	}

	bool AComponent::operator!=(const AComponent& other) const
	{
		return GetName() != other.GetName() ||
		       m_EntityRef.GetID() != other.GetOwner().GetID();
	}
}
