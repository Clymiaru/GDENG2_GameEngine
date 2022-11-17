#pragma once
#include "EntityRegistry.h"

namespace Engine
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		EntityRegistry& GetEntityRegistry();
		
	private:
		static EntityManager* s_Instance;
		
		EntityRegistry m_EntityRegistry;
	};

}
