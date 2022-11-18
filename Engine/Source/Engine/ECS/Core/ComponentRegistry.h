#pragma once
#include "AComponent.h"

namespace Engine
{
	using EntityID = uint64_t;
	
	class ComponentRegistry final
	{
	public:
		ComponentRegistry();
		~ComponentRegistry();

		void RegisterComponent(const EntityID& entityID, AComponent* component);
		
		[[nodiscard]]
		bool HasComponent(const EntityID& entityID, StringView componentType) const;

		// Gets a list of components attached with the given entity.
		List<AComponent*>& GetComponentListOfEntity(const EntityID& entityID);

		// Gets a reference of the list of components of the given ComponentType
		List<AComponent*>& GetComponentListOfType(StringView componentType);

		// Gets a component of type that attached with the given entity.
		template <typename ComponentType>
		ComponentType* GetComponent(const EntityID& entityID);
		
		void DeregisterComponent(const EntityID& entityID, StringView componentType);

		void DeregisterAllComponentsOfEntity(const EntityID& entityID);

		void DeregisterAllComponents();
		
		ComponentRegistry(const ComponentRegistry&)                = delete;
		ComponentRegistry& operator=(const ComponentRegistry&)     = delete;
		ComponentRegistry(ComponentRegistry&&) noexcept            = delete;
		ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;
		
	private:
		List<EntityID> m_EntitiesRegistered{};
		HashMap<EntityID, List<AComponent*>> m_EntityToComponentListMap{};
		HashMap<String, List<AComponent*>> m_ComponentListMap{};
	};
	
	template <typename ComponentType>
	ComponentType* ComponentRegistry::GetComponent(const EntityID& entityID)
	{
		if (!HasComponent(entityID, ComponentType::GetStaticName()))
		{
			return nullptr;
		}

		auto componentList = GetComponentListOfType(ComponentType::GetStaticName());

		const auto foundComponent = std::ranges::find_if(componentList,
														 [entityID](const AComponent* component) -> bool
														 {
															 return component->GetOwnerID() == entityID;
														 });

		if (foundComponent == componentList.end())
		{
			return nullptr;
		}
		return (ComponentType*)foundComponent;
	}
}
