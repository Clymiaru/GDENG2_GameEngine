#include "pch.h"
#include "AComponent.h"

namespace Engine
{
	AComponent::AComponent(Entity* owner) :
		m_EntityRef{owner}
	{
	}

	AComponent::~AComponent()
	{
		// Remove reference of this component to the entity
		// Have entity remove this component to its registry
		m_EntityRef = nullptr;
	}
}

