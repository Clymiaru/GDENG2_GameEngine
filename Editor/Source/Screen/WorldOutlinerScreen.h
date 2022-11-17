#pragma once
#include <Engine/Core/Core.h>
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
		explicit WorldOutlinerScreen(Engine::ScreenID id);

		~WorldOutlinerScreen() override;

		// Engine::Entity* GetSelectedEntity() const;

	private:
		void DrawImpl() override;

		
		// int m_IsSelected;
		//
		// Engine::List<Engine::Entity*>& m_EntitiesRef;
		// Engine::List<std::pair<int, bool>> m_SelectedEntities;
	};
}
