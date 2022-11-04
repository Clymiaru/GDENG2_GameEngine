#include "pch.h"
#include "AComponent.h"

#include "Engine/ECS/Entity/Entity.h"

namespace Engine
{
	AComponent::AComponent(Entity& owner) :
		m_EntityRef{owner}
	{
	}

	AComponent::~AComponent()
	{
		// Remove component at EntityRef?
	}

	Entity& AComponent::GetOwner() const
	{
		return m_EntityRef;
	}

	bool AComponent::operator==(const AComponent& other) const
	{
		return GetName() == other.GetName() &&
		       m_EntityRef.Name() == other.GetOwner().Name();
	}

	bool AComponent::operator!=(const AComponent& other) const
	{
		return GetName() != other.GetName() ||
		       m_EntityRef.Name() != other.GetOwner().Name();
	}
}
