#pragma once

#include "Engine/Core/Core.h"

namespace Engine
{
	class TransformComponent;
	class RenderComponent;
	class Entity
	{
	public:
		explicit Entity(const String& name);
		virtual ~Entity();

		const String& Name();
		TransformComponent& Transform() const;
		RenderComponent& Render() const;
	private:
		String m_Name;
		TransformComponent* m_Transform;
		RenderComponent* m_RenderComponent;
	};

}
