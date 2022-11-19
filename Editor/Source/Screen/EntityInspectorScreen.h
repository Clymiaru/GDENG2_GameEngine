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

		void Reset();

		void DrawComponents(const Engine::Entity* selectedEntity,
		                    Engine::List<Engine::SharedPtr<Engine::AComponent>> componentList);

		void DrawTransform(Engine::StringView entityNameID,
		                   Engine::SharedPtr<Engine::TransformComponent> transform) const;

		void DrawRender(Engine::StringView entityNameID,
		                Engine::SharedPtr<Engine::RenderComponent> render) const;

		// Event Callbacks
		void OnEntityDestroy(const Engine::Entity* entity);

		WorldOutlinerScreen& m_WorldOutlinerScreenRef;

		bool m_IsLocked = false;

		bool m_IsDeletingObject = false;

		Engine::List<Engine::String> m_ComponentList =
		{
			"Transform",
			"Render"
		};

		Engine::EntityID m_CurrentEntityID = 0;
	};
}
