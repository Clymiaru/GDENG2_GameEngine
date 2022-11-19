#pragma once
#include <functional>

#include "AComponent.h"

namespace Engine
{
	using EntityID = uint64_t;
	using ComponentEventCallback = std::function<void(const EntityID&, const AComponent*)>;

	class ComponentRegistry final
	{
	public:
		ComponentRegistry();
		~ComponentRegistry();

		template <typename ComponentType>
		[[nodiscard]]
		bool HasComponent(const EntityID& entityID) const;

		template <typename ComponentType>
		SharedPtr<ComponentType> RegisterComponent(const EntityID& entityID, SharedPtr<ComponentType> component);

		// Gets a component of type that attached with the given entity.
		template <typename ComponentType>
		SharedPtr<ComponentType> GetComponent(const EntityID& entityID);

		// Gets a reference of the list of components of the given ComponentType
		template <typename ComponentType>
		List<SharedPtr<ComponentType>> GetComponentListOfType();

		// Gets a list of components attached with the given entity.
		List<SharedPtr<AComponent>>& GetComponentListOfEntity(const EntityID& entityID);

		template <typename ComponentType>
		void DeregisterComponent(const EntityID& entityID);

		void DeregisterAllComponentsOfEntity(const EntityID& entityID);

		void DeregisterAllComponents();

		void ListenToAttachComponentEvent(const ComponentEventCallback& callback);

		void ListenToDetachComponentEvent(const ComponentEventCallback& callback);

		ComponentRegistry(const ComponentRegistry&)                = delete;
		ComponentRegistry& operator=(const ComponentRegistry&)     = delete;
		ComponentRegistry(ComponentRegistry&&) noexcept            = delete;
		ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;

	private:
		List<EntityID> m_EntitiesRegistered{};
		HashMap<EntityID, List<SharedPtr<AComponent>>> m_EntityToComponentListMap{};
		HashMap<String, List<SharedPtr<AComponent>>> m_ComponentListMap{};

		List<ComponentEventCallback> m_OnEntityAttachComponentCallbackList{};
		List<ComponentEventCallback> m_OnEntityDetachComponentCallbackList{};
	};

	template <typename ComponentType>
	bool ComponentRegistry::HasComponent(const EntityID& entityID) const
	{
		if (!m_EntityToComponentListMap.contains(entityID))
		{
			return false;
		}

		for (const auto componentList = m_EntityToComponentListMap.find(entityID)->second;
		     auto& component : componentList)
		{
			if (component->GetName() == ComponentType::GetStaticName())
			{
				return true;
			}
		}
		return false;
	}

	template <typename ComponentType>
	SharedPtr<ComponentType> ComponentRegistry::RegisterComponent(const EntityID& entityID,
	                                                              SharedPtr<ComponentType> component)
	{
		if (HasComponent<ComponentType>(entityID))
		{
			return GetComponent<ComponentType>(entityID);;
		}

		m_EntitiesRegistered.push_back(entityID);
		m_EntityToComponentListMap[entityID].push_back(std::dynamic_pointer_cast<AComponent>(component));
		m_ComponentListMap[ComponentType::GetStaticName()].push_back(std::dynamic_pointer_cast<AComponent>(component));

		// for (auto callback : m_OnEntityAttachComponentCallbackList)
		// {
		// 	callback(entityID, component);
		// }
		return component;
	}

	template <typename ComponentType>
	List<SharedPtr<ComponentType>> ComponentRegistry::GetComponentListOfType()
	{
		List<SharedPtr<ComponentType>> componentListOfType;
		if (!m_ComponentListMap.contains(ComponentType::GetStaticName()))
		{
			return componentListOfType;
		}

		auto componentList = m_ComponentListMap[ComponentType::GetStaticName()];

		for (size_t i = 0ULL; i < componentList.size(); i++)
		{
			componentListOfType.push_back(std::dynamic_pointer_cast<ComponentType>(componentList[i]));
		}
		return componentListOfType;
	}

	template <typename ComponentType>
	SharedPtr<ComponentType> ComponentRegistry::GetComponent(const EntityID& entityID)
	{
		if (!HasComponent<ComponentType>(entityID))
		{
			return nullptr;
		}

		List<SharedPtr<ComponentType>> componentList = GetComponentListOfType<ComponentType>();

		for (size_t i = 0; i < componentList.size(); i++)
		{
			if (componentList[i]->GetOwnerID() == entityID)
			{
				return componentList[i];	
			}
		}
		return nullptr;
	}

	template <typename ComponentType>
	void ComponentRegistry::DeregisterComponent(const EntityID& entityID)
	{
		if (!HasComponent<ComponentType>(entityID))
		{
			return;
		}
		String componentTypeName = ComponentType::GetStaticName();

		int index = -1;
		for (size_t i = 0; i < m_ComponentListMap[componentTypeName].size(); i++)
		{
			if (m_ComponentListMap[componentTypeName][i]->GetOwnerID() == entityID)
			{
				index = i;
			}
		}
		m_ComponentListMap[componentTypeName].erase(m_ComponentListMap[componentTypeName].begin() + index);
		m_ComponentListMap[componentTypeName].shrink_to_fit();
		if (m_ComponentListMap[componentTypeName].size() <= 0)
		{
			m_ComponentListMap.erase(componentTypeName);
		}

		index = -1;
		for (size_t i = 0; i < m_EntityToComponentListMap[entityID].size(); i++)
		{
			if (m_EntityToComponentListMap[entityID][i]->GetName() == componentTypeName)
			{
				index = i;
			}
		}
		m_EntityToComponentListMap[entityID].erase(m_EntityToComponentListMap[entityID].begin() + index);
		m_EntityToComponentListMap[entityID].shrink_to_fit();
		if (m_EntityToComponentListMap[entityID].size() <= 0)
		{
			m_EntityToComponentListMap.erase(entityID);
		}

		index = -1;
		for (size_t i = 0; i < m_EntitiesRegistered.size(); i++)
		{
			if (m_EntitiesRegistered[i] == entityID)
			{
				index = i;
			}
		}
		m_EntitiesRegistered.erase(m_EntitiesRegistered.begin() + index);
		m_EntitiesRegistered.shrink_to_fit();
	}
}
