#pragma once

#include "Engine/Core/Debug.h"

// Remember:
// Entity are ID
// Components are Data
// System are DataProcessors

// Architecture:
// 1 Entity : 1 Component type (An entity can only have 1 TransformComponent at any given time)

namespace Engine
{
	using EntityID = uint64_t;
	class Entity
	{
	public:
		explicit Entity(EntityID id);

		virtual ~Entity();

		[[nodiscard]]
		EntityID GetID() const;

		static Entity& Create();
		
		// template <typename T, typename... Args>
		// T& AttachComponent(Args&&... args);
		//
		// template <typename T>
		// void DetachComponent();
		//
		// template <class T>
		// T* GetComponent();

		// TODO: What to do for copying
		// Idea is that all component's data will be copied
		Entity(const Entity& other);
		Entity& operator=(const Entity& other);
		Entity(Entity&& other) noexcept;
		Entity& operator=(Entity&& other) noexcept;

		bool Active{};
		
	private:
		EntityID m_ID;
	};

	// template <typename T, typename ... Args>
	// T& Entity::AttachComponent(Args&&... args)
	// {
	// 	// Register this entity on the component's system
	//
	//
	// 	
	// 	T* component = nullptr;
	// 	if (m_ComponentTable.contains(T::GetStaticName()))
	// 	{
	// 		Debug::Log("Attempting to Attach {0} that is already attached to {1}!",
	// 		           T::GetStaticName(),
	// 		           Name.c_str());
	// 		component = (T*)m_ComponentTable[T::GetStaticName()];
	// 		return *component;
	// 	}
	//
	// 	component = new T(std::forward<Args>(args)...);
	// 	m_ComponentTable[T::GetStaticName()] = component;
	// 	
	// 	return *component;
	// }
	//
	// template <typename T>
	// void Entity::DetachComponent()
	// {
	// 	if (!m_ComponentTable.contains(T::GetStaticName()))
	// 	{
	// 		return;
	// 	}
	//
	// 	T* component = m_ComponentTable[T::GetStaticName()];
	// 	m_ComponentTable.erase(T::GetStaticName());
	// 	delete component;
	// }
	//
	// template <class T>
	// T* Entity::GetComponent()
	// {
	// 	auto foundComponent = m_ComponentTable.find(T::GetStaticName());
	// 	return (foundComponent != m_ComponentTable.end()) ?
	// 		       (T*)foundComponent->second :
	// 		       nullptr;
	// }
}
