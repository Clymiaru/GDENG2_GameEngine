#include "pch.h"
#include "AComponent.h"

namespace Engine
{
	AComponent::AComponent(const EntityID& ownerID) :
		m_OwnerID{ownerID} { }

	AComponent::~AComponent() = default;

	const EntityID& AComponent::GetOwnerID() const
	{
		return m_OwnerID;
	}

	EntityID AComponent::GetOwnerID()
	{
		return m_OwnerID;
	}

	bool AComponent::operator==(const AComponent& other) const
	{
		return GetName() == other.GetName() &&
		       m_OwnerID == other.m_OwnerID;
	}

	bool AComponent::operator!=(const AComponent& other) const
	{
		return GetName() != other.GetName() ||
		       m_OwnerID != other.m_OwnerID;
	}
}
