#pragma once
#include <Engine/Core/Core.h>
#include <Engine/ECS/Core/Entity.h>
#include <Engine/UI/AUIScreen.h>

namespace Engine
{
	class Entity;
}

namespace Editor
{
	// UI that shows all of the Entities in the scene
	class WorldOutlinerScreen final : public Engine::AUIScreen
	{
	public:
		struct Entry
		{
			Engine::EntityID EntityID = 0;
			Engine::String EntityName = "Unnamed";
			bool IsSelected           = false;
		};

		explicit WorldOutlinerScreen(Engine::ScreenID id);

		~WorldOutlinerScreen() override;

		[[nodiscard]]
		Engine::EntityID GetSelectedEntityID() const;

		WorldOutlinerScreen(const WorldOutlinerScreen&)                = delete;
		WorldOutlinerScreen& operator=(const WorldOutlinerScreen&)     = delete;
		WorldOutlinerScreen(WorldOutlinerScreen&&) noexcept            = delete;
		WorldOutlinerScreen& operator=(WorldOutlinerScreen&&) noexcept = delete;

	private:
		void DrawImpl() override;

		void AddEntityEntry(const Engine::Entity* entity);

		void RemoveEntityEntry(const Engine::Entity* entity);

		Engine::List<Entry> m_EntityEntryList;
		Engine::EntityID m_SelectedEntity = 0;
	};
}
