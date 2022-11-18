#pragma once
#include "AComponent.h"

namespace Engine
{
	class Entity;
	using EntityID = uint64_t;
	
	class ComponentRegistry final
	{
	public:
		ComponentRegistry();
		~ComponentRegistry();

		void RegisterComponent(Entity* entity, AComponent* component);
		
		[[nodiscard]]
		bool HasComponent(const Entity* entity, StringView componentType) const;

		List<AComponent*> GetComponentsOfEntity(const Entity* entity);
		
		// AComponent* GetComponent(Entity* entity, String componentType);
		
		void DeregisterComponent(Entity* entity, StringView componentType);
		
		ComponentRegistry(const ComponentRegistry&)                = delete;
		ComponentRegistry& operator=(const ComponentRegistry&)     = delete;
		ComponentRegistry(ComponentRegistry&&) noexcept            = delete;
		ComponentRegistry& operator=(ComponentRegistry&&) noexcept = delete;
		
	private:
		HashMap<EntityID, List<AComponent*>> m_EntityToComponentListMap{};
		HashMap<String, List<AComponent*>> m_ComponentListMap{};
	};
}
