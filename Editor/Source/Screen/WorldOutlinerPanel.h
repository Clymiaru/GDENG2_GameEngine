#pragma once
#include <Engine/UI/AUIPanel.h>

namespace Engine
{
	class Entity;
}

namespace Editor
{
	class WorldOutlinerPanel : public Engine::AUIPanel
	{
	public:
		explicit WorldOutlinerPanel(Engine::List<Engine::Entity*>& entityRef);

		~WorldOutlinerPanel() override;

		Engine::Entity* GetSelectedEntity() const;

	private:
		void DrawImpl() override;
		
		int m_IsSelected;
		
		Engine::List<Engine::Entity*>& m_EntitiesRef;
		Engine::List<std::pair<int, bool>> m_SelectedEntities;
	};
}
