#pragma once

#include "Engine/Core/Core.h"
namespace Engine
{
	class TransformComponent;
	class AComponent;
	// Let's try entity without TransformComponent
	// This is so an entity with pure data is possible?
	class Entity
	{
	public:
		explicit Entity(const String& name);
		virtual ~Entity();

		template <typename T, typename... Args>
		T& Attach(Args&&... args);

		template <typename T>
		T& Detach();

		const String& Name();
		TransformComponent& Transform() const;

		// TODO: What to do for copying
		Entity(const Entity&) = delete;
	
		Entity& operator=(const Entity& v) = delete;
	
		Entity(Entity&&) noexcept = delete;
	
		Entity& operator=(Entity&&) noexcept = delete;
	protected:
		String m_Name;
		bool m_IsEnabled;

		// For our engine case, only 1 component type is
		// able to be added to an object at anytime. (i.e. 1 TransformComponent max)
		// TODO: IF UUID approach, change String to uint128_t?
		
		HashMap<String, AComponent*> m_ComponentList;
		
		TransformComponent* m_Transform;
	};

	template <typename T, typename ... Args>
	T& Entity::Attach(Args&&... args)
	{
		// Check if the component exist
		// if yes, return component in this entity and log a warn message in the console.

		// if not, add this component
		T* component = new T(std::forward<Args>(args)...);
		m_ComponentList[T::GetStaticName()] = component;
		return *component;
	}

	template <typename T>
	T& Entity::Detach()
	{
	}
}
