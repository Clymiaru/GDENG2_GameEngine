#pragma once
#include <Engine/Core/Core.h>
#include <Engine/UI/AUIScreen.h>

namespace Engine
{
	class Entity;
}

namespace Editor
{
	class WorldOutlinerPanel;

	class EntityPropertiesPanel : public Engine::AUIScreen
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
