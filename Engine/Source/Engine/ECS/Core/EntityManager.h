#pragma once
#include <format>
#include <functional>

#include "EntityRegistry.h"
#include "ComponentRegistry.h"

#include "Utils/UIIDGenerator.h"

namespace Engine
{
	class EntityManager final
	{
	public:
		EntityManager();
		~EntityManager();

		template <typename EntityType, typename... Args>
		static EntityType* Create(Args&&... args);

		static void Destroy(EntityID id);

		static Entity* GetEntity(EntityID id);

		static const List<Entity*>& GetAllEntities();

		static List<AComponent*> GetAllComponentsOfEntity(EntityID entity);

		// template <typename ComponentType, typename... Args>
		// static void AttachComponentToEntity(EntityID id, Args&&... args);

		static void ListenToCreateEvent(std::function<void(EntityID, StringView)> onCreateCallback);

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

		List<std::function<void(EntityID, StringView)>> m_OnCreateCallback;
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

		for (auto callback : s_Instance->m_OnCreateCallback)
		{
			callback(newEntityID, newEntityName);
		}

		return newEntity;
	}

	// template <typename ComponentType, typename ... Args>
	// void EntityManager::AttachComponentToEntity(EntityID id,  Args&&... args)
	// {
	// 	if (!s_Instance->m_EntityToComponentListMap.contains(id))
	// 	{
	// 		return;
	// 	}
	//
	// 	auto& componentList = s_Instance->m_EntityToComponentListMap[id];
	//
	// 	int index = -1;
	// 	for (size_t i = 0; i < componentList.size(); i++)
	// 	{
	// 		if (componentList[i]->GetName() == ComponentType::GetStaticName())
	// 		{
	// 			index = i;
	// 		}
	// 	}
	//
	// 	if (index != -1)
	// 		return;
	//
	// 	ComponentType* newComponent = new ComponentType(*s_Instance->m_EntityMap[id], std::forward<Args>(args)...);
	// 	componentList.push_back(newComponent);
	// }
}
