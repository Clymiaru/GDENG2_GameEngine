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

		for (auto callback : s_Instance->m_OnDestroyEntityCallbackList)
		{
			callback(entity);
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
	
	List<SharedPtr<AComponent>> EntityManager::GetAllComponentsOfEntity(const EntityID entityID)
	{
		return s_Instance->m_ComponentRegistry.GetComponentListOfEntity(entityID);
	}
	
	void EntityManager::ListenToEntityCreateEvent(const EntityEventCallback& callback)
	{
		s_Instance->m_OnCreateEntityCallbackList.push_back(callback);
	}
	
	void EntityManager::ListenToEntityDestroyEvent(const EntityEventCallback& callback)
	{
		s_Instance->m_OnDestroyEntityCallbackList.push_back(callback);
	}
	
	void EntityManager::ListenToEntityAttachComponentEvent(const ComponentEventCallback& callback)
	{
		s_Instance->m_ComponentRegistry.ListenToAttachComponentEvent(callback);
	}
	
	void EntityManager::ListenToEntityDetachComponentEvent(const ComponentEventCallback& callback)
	{
		s_Instance->m_ComponentRegistry.ListenToDetachComponentEvent(callback);
	}
}
