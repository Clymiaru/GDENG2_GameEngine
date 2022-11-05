#pragma once

#include "Engine/Core/Debug.h"

namespace Engine
{
	class TransformComponent;

	class AComponent;

	// Let's try entity without TransformComponent
	// This is so an entity with pure data is possible?

	// Assume that all Entities have Transform
	class Entity
	{
	public:
		explicit Entity(StringView name);

		virtual ~Entity();

		template <typename T, typename... Args>
		T& AttachComponent(Args&&... args);

		template <typename T>
		void DetachComponent();

		template <class T>
		T* GetComponent();

		[[nodiscard]]
		TransformComponent& Transform() const;

		// TODO: Consider this 2 functions if Entity is like Unity's Monobehavior
		// void Update(float deltaTime);
		// void Draw();

		// TODO: What to do for copying
		// Idea is that all component's data will be copied
		Entity(const Entity&) = delete;

		Entity& operator=(const Entity& v) = delete;

		Entity(Entity&&) noexcept = delete;

		Entity& operator=(Entity&&) noexcept = delete;

		String Name;

		bool Active{};

	protected:
		// For our engine case, only 1 component type is
		// able to be added to an object at anytime. (i.e. 1 TransformComponent max)
		// TODO: IF UUID approach, change String to uint128_t?

		HashMap<String, AComponent*> m_ComponentTable{};

		TransformComponent* m_Transform;
	};

	template <typename T, typename ... Args>
	T& Entity::AttachComponent(Args&&... args)
	{
		T* component = nullptr;
		if (m_ComponentTable.contains(T::GetStaticName()))
		{
			Debug::Log("Attempting to Attach {0} that is already attached to {1}!",
			           T::GetStaticName(),
			           Name.c_str());
			component = (T*)m_ComponentTable[T::GetStaticName()];
			return *component;
		}

		component = new T(std::forward<Args>(args)...);
		m_ComponentTable[T::GetStaticName()] = component;
		
		return *component;
	}

	template <typename T>
	void Entity::DetachComponent()
	{
		if (!m_ComponentTable.contains(T::GetStaticName()))
		{
			return;
		}

		T* component = m_ComponentTable[T::GetStaticName()];
		m_ComponentTable.erase(T::GetStaticName());
		delete component;
	}

	template <class T>
	T* Entity::GetComponent()
	{
		auto foundComponent = m_ComponentTable.find(T::GetStaticName());
		return (foundComponent != m_ComponentTable.end()) ?
			       (T*)foundComponent->second :
			       nullptr;
	}
}
