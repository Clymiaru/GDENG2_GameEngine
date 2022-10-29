#pragma once

namespace Engine
{
	class Entity;
	class AComponent
	{
	public:
		AComponent(Entity* owner);
		virtual ~AComponent();
	protected:
		Entity* m_EntityRef = nullptr;
	};
}
