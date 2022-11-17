#pragma once
#include <queue>

#include "AComponent.h"
#include "Entity.h"

#include "Utils/UIIDGenerator.h"

namespace Engine
{
	class EntityRegistry final
	{
	public:
		EntityRegistry();
		
		~EntityRegistry();
		
		Entity& CreateEntity();

		bool HasEntity(const Entity& entity) const;
		
		void DestroyEntity(Entity& entity);

		template <typename ComponentType>
		void RegisterComponent(Entity& entity);

		template <typename ComponentType>
		void DeregisterComponent(Entity& entity);

		// TODO: Get functionality

	private:
		UIIDGenerator m_EntityUIIDGenerator;

		List<Entity*> m_EntityList;
		
		HashMap<EntityID, Entity*> m_EntityMap;
		
		// Entity - ComponentList directory
		HashMap<EntityID, List<AComponent*>> m_EntityToComponentListMap;
		
		// ComponentType - ComponentList directory
		HashMap<String, List<AComponent*>> m_ComponentMap; // Why have this?
	};
}
