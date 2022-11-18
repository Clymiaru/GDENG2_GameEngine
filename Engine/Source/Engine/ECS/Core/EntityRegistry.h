#pragma once
#include "Entity.h"

namespace Engine
{
	class EntityRegistry final
	{
	public:
		EntityRegistry();
		
		~EntityRegistry();

		void RegisterEntity(Entity* entity);

		[[nodiscard]]
		bool HasEntity(const Entity& entity) const;

		[[nodiscard]]
		bool HasEntity(const EntityID& id) const;

		Entity* GetEntity(const EntityID& id);

		// Retrieves a list of entities with the same name
		[[nodiscard]]
		List<Entity*> GetEntitiesByName(StringView name) const;

		[[nodiscard]]
		const List<Entity*>& GetAllEntities() const;

		void DeregisterEntity(const Entity* entity);

		void DeregisterAllEntities();

		EntityRegistry(const EntityRegistry&)                = delete;
		EntityRegistry& operator=(const EntityRegistry&)     = delete;
		EntityRegistry(EntityRegistry&&) noexcept            = delete;
		EntityRegistry& operator=(EntityRegistry&&) noexcept = delete;

	private:
		List<Entity*> m_EntityList{};
		HashMap<EntityID, Entity*> m_EntityMap{};
	};
}