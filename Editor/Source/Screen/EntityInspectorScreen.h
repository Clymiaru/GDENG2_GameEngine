#pragma once
#include <Engine/Core/Core.h>
#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Component/RenderComponent.h>
#include <Engine/UI/AUIScreen.h>

#include "WorldOutlinerScreen.h"

namespace Engine
{
	class Entity;
}

namespace Editor
{
	class EntityInspectorScreen final : public Engine::AUIScreen
	{
	public:
		explicit EntityInspectorScreen(Engine::ScreenID id,
		                               WorldOutlinerScreen& worldOutlinerScreenRef);

		~EntityInspectorScreen() override;

		EntityInspectorScreen(const EntityInspectorScreen&)                = delete;
		EntityInspectorScreen& operator=(const EntityInspectorScreen&)     = delete;
		EntityInspectorScreen(EntityInspectorScreen&&) noexcept            = delete;
		EntityInspectorScreen& operator=(EntityInspectorScreen&&) noexcept = delete;
	private:
		void DrawImpl() override;

		void DrawComponents(const Engine::Entity* selectedEntity,
		                    Engine::List<Engine::AComponent*> componentList);

		void DrawTransform(Engine::StringView entityNameID,
		                   Engine::TransformComponent* transform) const;

		void DrawRender(Engine::StringView entityNameID,
		                Engine::RenderComponent* render) const;

		WorldOutlinerScreen& m_WorldOutlinerScreenRef;

		bool m_IsLocked = false;

		Engine::EntityID m_CurrentEntityID = 0;
	};
}
