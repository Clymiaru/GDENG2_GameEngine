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
	
	class WorldOutlinerScreen final: public Engine::AUIScreen
	{
	public:
		struct Entry
		{
			Engine::EntityID EntityID;
			Engine::String EntityName;
			bool IsSelected = false;
		};
		explicit WorldOutlinerScreen(Engine::ScreenID id);
		~WorldOutlinerScreen() override;

		Engine::EntityID GetSelectedEntityID() const;

		WorldOutlinerScreen(const WorldOutlinerScreen&)                = delete;
		WorldOutlinerScreen& operator=(const WorldOutlinerScreen&)     = delete;
		WorldOutlinerScreen(WorldOutlinerScreen&&) noexcept            = delete;
		WorldOutlinerScreen& operator=(WorldOutlinerScreen&&) noexcept = delete;

	private:
		void DrawImpl() override;

		void OnEntityCreate(Engine::EntityID entityID, Engine::StringView entityName);

		void OnEntityDestroy(Engine::EntityID entityID, Engine::StringView entityName);

		Engine::List<Entry> m_EntityEntryList;

		Engine::EntityID m_SelectedEntity = 0;

	};
}
