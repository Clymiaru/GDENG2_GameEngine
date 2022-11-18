#include "pch.h"
#include "EntityManager.h"

namespace Engine
{
	EntityManager* EntityManager::s_Instance = nullptr;

	EntityManager::EntityManager() :
		m_EntityUIIDGenerator{UIIDGenerator()}
	{
		Debug::Assert(s_Instance == nullptr,
		              "EntityManager has already been instantiated and initialized!");

		s_Instance = this;
	}

	EntityManager::~EntityManager()
	{
		// Clear entity list
		s_Instance = nullptr;
	}
	
	void EntityManager::Destroy(const EntityID id)
	{
		if (!s_Instance->m_EntityRegistry.HasEntity(id))
			return;

		const auto* entityRef = s_Instance->m_EntityRegistry.GetEntity(id);

		s_Instance->m_EntityUIIDGenerator.AddReservedUIID(id);

		s_Instance->m_EntityRegistry.DeregisterEntity(entityRef);

		delete entityRef;
	}
	
	Entity* EntityManager::GetEntity(EntityID id)
	{
		return s_Instance->m_EntityRegistry.GetEntity(id);
	}
	
	const List<Entity*>& EntityManager::GetAllEntities()
	{
		return s_Instance->m_EntityRegistry.GetAllEntities();
	}
	
	List<AComponent*> EntityManager::GetAllComponentsOfEntity(const EntityID entity)
	{
		return s_Instance->m_ComponentRegistry.GetComponentsOfEntity(s_Instance->m_EntityRegistry.GetEntity(entity));
	}

	void EntityManager::ListenToCreateEvent(const std::function<void(EntityID, StringView)> onCreateCallback)
	{
		s_Instance->m_OnCreateCallback.push_back(onCreateCallback);
	}
}
