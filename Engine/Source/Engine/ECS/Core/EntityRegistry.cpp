#include "pch.h"
#include "EntityRegistry.h"

#include "Entity.h"

namespace Engine
{
	EntityRegistry::EntityRegistry() = default;
	
	EntityRegistry::~EntityRegistry()
	{
		DeregisterAllEntities();
	}

	void EntityRegistry::RegisterEntity(Entity* entity)
	{
		if (HasEntity(*entity))
		{
			return;
		}

		m_EntityMap[entity->GetID()] = entity;
		m_EntityList.push_back(entity);
	}

	bool EntityRegistry::HasEntity(const Entity& entity) const
	{
		return m_EntityMap.contains(entity.GetID());
	}

	bool EntityRegistry::HasEntity(const EntityID& id) const
	{
		return m_EntityMap.contains(id);
	}

	Entity* EntityRegistry::GetEntity(const EntityID& id)
	{
		if (!HasEntity(id))
		{
			return nullptr;
		}
		return m_EntityMap[id];
	}
	
	Entity* EntityRegistry::GetEntityByName(const StringView name) const
	{
		for (auto* entity : m_EntityList)
		{
			if (entity->GetName() == name)
			{
				return entity;
			}
		}
		return nullptr;
	}

	List<Entity*> EntityRegistry::GetEntitiesByName(const StringView name) const
	{
		List<Entity*> entities = List<Entity*>();

		for (auto* entity : m_EntityList)
		{
			if (entity->GetName() == name)
			{
				entities.push_back(entity);
			}
		}
		return entities;
	}
	
	const List<Entity*>& EntityRegistry::GetAllEntities() const
	{
		return m_EntityList;
	}

	void EntityRegistry::DeregisterEntity(const Entity* entity)
	{
		if (!HasEntity(*entity))
		{
			return;
		}

		auto* entityRef = m_EntityMap[entity->GetID()];

		auto entityIndex = std::ranges::remove(m_EntityList, entityRef);
		m_EntityList.erase(entityIndex.begin(), entityIndex.end());
		m_EntityList.shrink_to_fit();

		m_EntityMap.erase(entityRef->GetID());
	}

	void EntityRegistry::DeregisterAllEntities()
	{
		for (size_t i = 0; i < m_EntityList.size(); i++)
		{
			DeregisterEntity(m_EntityList[i]);
		}
	}
}
