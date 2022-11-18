#include "pch.h"
#include "ComponentRegistry.h"

#include "Entity.h"

namespace Engine
{
	ComponentRegistry::ComponentRegistry() = default;
	ComponentRegistry::~ComponentRegistry() = default;

	void ComponentRegistry::RegisterComponent(Entity* entity, AComponent* component)
	{
		if (HasComponent(entity, component->GetName()))
		{
			delete component;
			return;
		}

		m_EntityToComponentListMap[entity->GetID()].push_back(component);
		m_ComponentListMap[component->GetName()].push_back(component);
	}

	bool ComponentRegistry::HasComponent(const Entity* entity, StringView componentType) const
	{
		const EntityID entityID = entity->GetID();
		if (!m_EntityToComponentListMap.contains(entityID))
		{
			return false;
		}

		auto componentList = m_EntityToComponentListMap.find(entityID)->second;

		const auto foundComponent = std::ranges::find_if(componentList,
		                                                 [componentType](const AComponent* component) -> bool
		                                                 {
			                                                 return component->GetName() == componentType.data();
		                                                 });

		if (foundComponent == componentList.end())
		{
			return false;
		}

		return true;
	}
	
	List<AComponent*> ComponentRegistry::GetComponentsOfEntity(const Entity* entity)
	{
		return m_EntityToComponentListMap[entity->GetID()];
	}

	void ComponentRegistry::DeregisterComponent(Entity* entity, StringView componentType)
	{
		if (!HasComponent(entity, componentType))
		{
			return;
		}

		List<AComponent*>& componentList = m_ComponentListMap[componentType.data()];

		auto foundComponent = std::ranges::remove_if(componentList,
		                                             [entity](const AComponent* component) -> bool
		                                             {
			                                             return component->GetOwner().GetID() == entity->GetID();
		                                             });
		componentList.erase(foundComponent.begin(), foundComponent.end());
		componentList.shrink_to_fit();

		componentList = m_EntityToComponentListMap[entity->GetID()];

		foundComponent = std::ranges::remove_if(componentList,
		                                        [componentType](const AComponent* component) -> bool
		                                        {
			                                        return component->GetName() == componentType.data();
		                                        });
		componentList.erase(foundComponent.begin(), foundComponent.end());
		componentList.shrink_to_fit();
	}
}
