#pragma once
#include <format>
#include <functional>

#include "EntityRegistry.h"
#include "ComponentRegistry.h"

#include "Utils/UIIDGenerator.h"

namespace Engine
{
	using EntityEventCallback = std::function<void(const Entity*)>;

	class EntityManager final
	{
	public:
		EntityManager();
		~EntityManager();

		template <typename EntityType, typename... Args>
		static EntityType* Create(StringView name = "Entity", Args&&... args);

		static void Destroy(const Entity* entity);

		// Returns the entity instance found with the given ID
		static Entity* GetEntity(EntityID id);

		// Returns the first entity instance found with the given name
		static Entity* GetEntityByName(StringView entityName);

		// Returns the all entity instances found with the given name
		static List<Entity*> GetEntitiesByName(StringView entityName);

		// Returns all entity instances ever created with Entity Manager
		static const List<Entity*>& GetAllEntities();

		// Returns a list of all the components of an entity of given ID
		static List<SharedPtr<AComponent>> GetAllComponentsOfEntity(EntityID entityID);

		template <typename ComponentType>
		static List<SharedPtr<ComponentType>> GetAllComponentsOfType();

		static void ListenToEntityCreateEvent(const EntityEventCallback& callback);

		static void ListenToEntityDestroyEvent(const EntityEventCallback& callback);

		static void ListenToEntityAttachComponentEvent(const ComponentEventCallback& callback);

		static void ListenToEntityDetachComponentEvent(const ComponentEventCallback& callback);

		EntityManager(const EntityManager&)                = delete;
		EntityManager& operator=(const EntityManager&)     = delete;
		EntityManager(EntityManager&&) noexcept            = delete;
		EntityManager& operator=(EntityManager&&) noexcept = delete;
	private:
		static EntityManager* s_Instance;

		UIIDGenerator m_EntityUIIDGenerator;

		EntityRegistry m_EntityRegistry;

		ComponentRegistry m_ComponentRegistry;

		List<EntityEventCallback> m_OnCreateEntityCallbackList{};
		List<EntityEventCallback> m_OnDestroyEntityCallbackList{};
	};

	// TODO: Should we return ptr to created entity.
	// Issue may be deleting entity after creation outside of EntityManager
	template <typename EntityType, typename ... Args>
	EntityType* EntityManager::Create(StringView name, Args&&... args)
	{
		EntityID newEntityID = s_Instance->m_EntityUIIDGenerator.GenerateUIID();
		String newEntityName = std::vformat("{0}_{1}", std::make_format_args(name, newEntityID));

		EntityType* newEntity = new EntityType(newEntityID,
		                                       newEntityName,
		                                       &s_Instance->m_ComponentRegistry,
		                                       std::forward<Args>(args)...);

		s_Instance->m_EntityRegistry.RegisterEntity((Entity*)newEntity);

		for (auto callback : s_Instance->m_OnCreateEntityCallbackList)
		{
			callback((Entity*)newEntity);
		}

		return newEntity;
	}
	
	template <typename ComponentType>
	List<SharedPtr<ComponentType>> EntityManager::GetAllComponentsOfType()
	{
		return s_Instance->m_ComponentRegistry.GetComponentListOfType<ComponentType>();
	}
}
