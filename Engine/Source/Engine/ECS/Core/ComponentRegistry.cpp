#include "pch.h"
#include "ComponentRegistry.h"

namespace Engine
{
	ComponentRegistry::ComponentRegistry()  = default;
	
	ComponentRegistry::~ComponentRegistry()
	{
		DeregisterAllComponents();
	}

	List<SharedPtr<AComponent>>& ComponentRegistry::GetComponentListOfEntity(const EntityID& entityID)
	{
		return m_EntityToComponentListMap[entityID];
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
			String componentTypeName = componentList[i]->GetName();

			auto foundComponent = std::ranges::remove_if(m_ComponentListMap[componentTypeName],
														 [entityID](const SharedPtr<AComponent> component) -> bool
														 {
															 return component->GetOwnerID() == entityID;
														 });
			m_ComponentListMap[componentTypeName].erase(foundComponent.begin(), foundComponent.end());
			m_ComponentListMap[componentTypeName].shrink_to_fit();
			if (m_ComponentListMap[componentTypeName].size() <= 0)
			{
				m_ComponentListMap.erase(componentTypeName);
			}

			foundComponent = std::ranges::remove_if(m_EntityToComponentListMap[entityID],
													[componentTypeName](const SharedPtr<AComponent> component) -> bool
													{
														return component->GetName() == componentTypeName;
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
	}

	void ComponentRegistry::DeregisterAllComponents()
	{
		for (size_t i = 0; i < m_EntitiesRegistered.size(); i++)
		{
			DeregisterAllComponentsOfEntity(m_EntitiesRegistered[i]);
		}
	}
	void ComponentRegistry::ListenToAttachComponentEvent(const ComponentEventCallback& callback)
	{
		m_OnEntityAttachComponentCallbackList.push_back(callback);
	}

	void ComponentRegistry::ListenToDetachComponentEvent(const ComponentEventCallback& callback)
	{
		m_OnEntityDetachComponentCallbackList.push_back(callback);
	}
}
