#pragma once

#include "Engine/Core/Core.h"
namespace Engine
{
	class TransformComponent;
	// Let's try entity without TransformComponent
	// This is so an entity with pure data is possible?
	class Entity
	{
	public:
		explicit Entity(const String& name);
		virtual ~Entity();

		const String& Name();
		TransformComponent& Transform() const;

		// TODO: What to do for copying
		Entity(const Entity&) = delete;
	
		Entity& operator=(const Entity& v) = delete;
	
		Entity(Entity&&) noexcept = delete;
	
		Entity& operator=(Entity&&) noexcept = delete;
	protected:
		String m_Name;
		TransformComponent* m_Transform;
	};

}
