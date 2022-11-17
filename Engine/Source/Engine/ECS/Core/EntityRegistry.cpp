#include "pch.h"
#include "EntityRegistry.h"

namespace Engine
{
	EntityRegistry::EntityRegistry() :
		m_EntityUIIDGenerator{UIIDGenerator()},
		m_EntityList{},
		m_EntityToComponentListMap{}
	{
		
	}
	
	EntityRegistry::~EntityRegistry()
	{
		// Destroy all entities in the registry
	}
	
	Entity& EntityRegistry::CreateEntity()
	{
		const EntityID entityID = m_EntityUIIDGenerator.GenerateUIID();
		Entity* entity = new Entity(entityID);

		m_EntityList.emplace_back(entity);
		m_EntityToComponentListMap[entityID] = List<AComponent*>();

		return *entity;
	}
	
	bool EntityRegistry::HasEntity(const Entity& entity) const
	{
		return m_EntityMap.contains(entity.GetID());
	}

	void EntityRegistry::DestroyEntity(Entity& entity)
	{
		// Find the entity first if it is in the registry
		if (!HasEntity(entity))
		{
			return; // Entity does not exists!
		}

		// How to destroy? (Immediate destroy for now)
		// TODO: Check if Immediate destroy is enough
		auto* entityRef = m_EntityMap[entity.GetID()];

		// Remove Entity in the list
		auto entityIndex = std::ranges::remove(m_EntityList, entityRef);
		m_EntityList.erase(entityIndex.begin(), entityIndex.end());
		m_EntityList.shrink_to_fit();

		// Remove Entity in the map
		m_EntityMap.erase(entityRef->GetID());
		
		// Remove all components from that entity in the ListMap and ComponentMap
		const auto deletedEntityComponentList = m_EntityToComponentListMap[entityRef->GetID()];

		for (size_t i = 0; i < deletedEntityComponentList.size(); i++)
		{
			auto component = deletedEntityComponentList[i]; 
			auto componentList = m_ComponentMap[component->GetName()];

			const auto foundComponent = std::ranges::find_if(componentList, [component](const AComponent* other) -> bool
			{
				return other->GetOwner().GetID() == component->GetOwner().GetID();
			});
			componentList.erase(foundComponent);
			
			delete deletedEntityComponentList[i];
		}

		m_EntityToComponentListMap.erase(entityRef->GetID());
		
		delete entityRef;
	}
}
