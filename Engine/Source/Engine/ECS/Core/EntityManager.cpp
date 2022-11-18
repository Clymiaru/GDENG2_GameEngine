#include "pch.h"
#include "EntityManager.h"

namespace Engine
{
	EntityManager* EntityManager::s_Instance = nullptr;

	EntityManager::EntityManager() :
		m_EntityUIIDGenerator{UIIDGenerator()},
		m_EntityRegistry{EntityRegistry()},
		m_ComponentRegistry{ComponentRegistry()}
	{
		Debug::Assert(s_Instance == nullptr,
		              "EntityManager has already been instantiated and initialized!");

		s_Instance = this;
	}

	EntityManager::~EntityManager()
	{
		// Clear all components and delete them
		// Clear all entities and delete them
		s_Instance = nullptr;
	}
	
	void EntityManager::Destroy(const Entity* entity)
	{
		if (!s_Instance->m_EntityRegistry.HasEntity(entity->GetID()))
			return;

		s_Instance->m_EntityUIIDGenerator.AddReservedUIID(entity->GetID());

		s_Instance->m_EntityRegistry.DeregisterEntity(entity);

		s_Instance->m_ComponentRegistry.DeregisterAllComponentsOfEntity(entity->GetID());

		for (auto callback : s_Instance->m_OnDestroyCallbackList)
		{
			callback(entity->GetID(), entity->GetName());
		}
		
		delete entity;
	}
	
	Entity* EntityManager::GetEntity(const EntityID id)
	{
		return s_Instance->m_EntityRegistry.GetEntity(id);
	}
	
	Entity* EntityManager::GetEntityByName(const StringView entityName)
	{
		return s_Instance->m_EntityRegistry.GetEntityByName(entityName);
	}
	
	List<Entity*> EntityManager::GetEntitiesByName(const StringView entityName)
	{
		return s_Instance->m_EntityRegistry.GetEntitiesByName(entityName);
	}

	const List<Entity*>& EntityManager::GetAllEntities()
	{
		return s_Instance->m_EntityRegistry.GetAllEntities();
	}
	
	List<AComponent*> EntityManager::GetAllComponentsOfEntity(const EntityID entityID)
	{
		return s_Instance->m_ComponentRegistry.GetComponentListOfEntity(entityID);
	}

	void EntityManager::ListenToCreateEvent(const std::function<void(EntityID, StringView)> onCreateCallback)
	{
		s_Instance->m_OnCreateCallbackList.push_back(onCreateCallback);
	}
	
	void EntityManager::ListenToDestroyEvent(std::function<void(EntityID, StringView)> onDestroyCallback)
	{
		s_Instance->m_OnDestroyCallbackList.push_back(onDestroyCallback);
	}
}
