#pragma once
#include <format>
#include <functional>

#include "EntityRegistry.h"
#include "ComponentRegistry.h"

#include "Utils/UIIDGenerator.h"
// Should I have each entity have an event trigger when they are destroyed?

namespace Engine
{
	class EntityManager final
	{
	public:
		EntityManager();
		~EntityManager();

		template <typename EntityType, typename... Args>
		static EntityType* Create(Args&&... args);

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
		static List<AComponent*> GetAllComponentsOfEntity(EntityID entityID);

		template <typename ComponentType>
		static List<ComponentType*> GetAllComponentsOfType();

		static void ListenToCreateEvent(std::function<void(EntityID, StringView)> onCreateCallback);

		static void ListenToDestroyEvent(std::function<void(EntityID, StringView)> onDestroyCallback);

		// static void ListenToAttachComponentEvent(std::function<void(EntityID, StringView)> onCreateCallback);

		EntityManager(const EntityManager&)                = delete;
		EntityManager& operator=(const EntityManager&)     = delete;
		EntityManager(EntityManager&&) noexcept            = delete;
		EntityManager& operator=(EntityManager&&) noexcept = delete;
	private:
		static EntityManager* s_Instance;

		UIIDGenerator m_EntityUIIDGenerator;

		EntityRegistry m_EntityRegistry;

		ComponentRegistry m_ComponentRegistry;

		List<std::function<void(EntityID, StringView)>> m_OnCreateCallbackList{};
		List<std::function<void(EntityID, StringView)>> m_OnDestroyCallbackList{};
	};

	// TODO: Should we return ptr to created entity.
	// Issue may be deleting entity after creation outside of EntityManager
	template <typename EntityType, typename ... Args>
	EntityType* EntityManager::Create(Args&&... args)
	{
		EntityID newEntityID = s_Instance->m_EntityUIIDGenerator.GenerateUIID();
		String newEntityName = std::vformat("Entity_{0}", std::make_format_args(newEntityID));

		EntityType* newEntity = new EntityType(newEntityID,
		                                       newEntityName,
		                                       &s_Instance->m_ComponentRegistry,
		                                       std::forward<Args>(args)...);

		s_Instance->m_EntityRegistry.RegisterEntity((Entity*)newEntity);

		for (auto callback : s_Instance->m_OnCreateCallbackList)
		{
			callback(newEntityID, newEntityName);
		}

		return newEntity;
	}
	
	template <typename ComponentType>
	List<ComponentType*> EntityManager::GetAllComponentsOfType()
	{
		List<ComponentType*> componentTypeList = List<ComponentType*>();
		List<AComponent*>& componentList = s_Instance->m_ComponentRegistry.GetComponentListOfType(ComponentType::GetStaticName());
		for (size_t i = 0ULL; i < componentList.size(); i++)
		{
			componentTypeList.push_back((ComponentType*)componentList[i]);
		}
		return componentTypeList;
	}
}
