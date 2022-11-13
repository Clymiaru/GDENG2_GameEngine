#pragma once
#include "Entity.h"
#include <queue>

namespace Engine
{
	class EntityManager final
	{
	public:
		Entity* CreateEntity();

		List<Entity*>& GetAllEntities();
	private:
		List<Entity*> m_EntityList;
		// std::queue<EntityID> m_ReservedEntityID;
	};
}
