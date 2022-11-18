#include "pch.h"
#include "ComponentRegistry.h"

namespace Engine
{
	ComponentRegistry::ComponentRegistry()  = default;
	
	ComponentRegistry::~ComponentRegistry()
	{
		DeregisterAllComponents();
	}

	void ComponentRegistry::RegisterComponent(const EntityID& entityID, AComponent* component)
	{
		if (HasComponent(entityID, component->GetName()))
		{
			delete component;
			return;
		}

		m_EntitiesRegistered.push_back(entityID);
		m_EntityToComponentListMap[entityID].push_back(component);
		m_ComponentListMap[component->GetName()].push_back(component);
	}

	bool ComponentRegistry::HasComponent(const EntityID& entityID, StringView componentType) const
	{
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

	List<AComponent*>& ComponentRegistry::GetComponentListOfEntity(const EntityID& entityID)
	{
		return m_EntityToComponentListMap[entityID];
	}

	List<AComponent*>& ComponentRegistry::GetComponentListOfType(const StringView componentType)
	{
		return m_ComponentListMap[componentType.data()];
	}

	void ComponentRegistry::DeregisterComponent(const EntityID& entityID, StringView componentType)
	{
		if (!HasComponent(entityID, componentType))
		{
			return;
		}

		auto foundComponent = std::ranges::remove_if(m_ComponentListMap[componentType.data()],
		                                             [entityID](const AComponent* component) -> bool
		                                             {
			                                             return component->GetOwnerID() == entityID;
		                                             });
		m_ComponentListMap[componentType.data()].erase(foundComponent.begin(), foundComponent.end());
		m_ComponentListMap[componentType.data()].shrink_to_fit();
		if (m_ComponentListMap[componentType.data()].size() <= 0)
		{
			m_ComponentListMap.erase(componentType.data());
		}


		foundComponent = std::ranges::remove_if(m_EntityToComponentListMap[entityID],
		                                        [componentType](const AComponent* component) -> bool
		                                        {
			                                        return component->GetName() == componentType.data();
		                                        });
		m_EntityToComponentListMap[entityID].erase(foundComponent.begin(), foundComponent.end());
		m_EntityToComponentListMap[entityID].shrink_to_fit();
		if (m_EntityToComponentListMap[entityID].size() <= 0)
		{
			m_EntityToComponentListMap.erase(entityID);
		}

		auto foundRegisteredEntity = std::ranges::remove_if(m_EntitiesRegistered,
		                                                    [entityID](const EntityID& registeredID) -> bool
		                                                    {
			                                                    return registeredID == entityID;
		                                                    });
		m_EntitiesRegistered.erase(foundRegisteredEntity.begin(), foundRegisteredEntity.end());
		m_EntitiesRegistered.shrink_to_fit();
	}

	void ComponentRegistry::DeregisterAllComponentsOfEntity(const EntityID& entityID)
	{
		if (!m_EntityToComponentListMap.contains(entityID))
		{
			return;
		}

		const auto componentList = m_EntityToComponentListMap.find(entityID)->second;

		for (size_t i = 0; i < componentList.size(); i++)
		{
			const AComponent* componentRef = componentList[i];
			DeregisterComponent(entityID, componentList[i]->GetName());
			delete componentRef;
		}
	}

	void ComponentRegistry::DeregisterAllComponents()
	{
		for (size_t i = 0; i < m_EntitiesRegistered.size(); i++)
		{
			DeregisterAllComponentsOfEntity(m_EntitiesRegistered[i]);
		}
	}
}
