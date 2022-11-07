#pragma once
#include <Engine/UI/AUIPanel.h>

namespace Engine
{
	class Entity;
}

namespace Editor
{
	class WorldOutlinerPanel;

	class EntityPropertiesPanel : public Engine::AUIPanel
	{
	public:
		EntityPropertiesPanel(WorldOutlinerPanel& worldOutlinerPanel,
		                      Engine::List<Engine::Entity*>& entityRef);

		~EntityPropertiesPanel() override;

	private:
		void DrawImpl() override;

		WorldOutlinerPanel& m_WorldOutlinerPanelRef;
		Engine::List<Engine::Entity*>& m_EntityRef;
	};
}
