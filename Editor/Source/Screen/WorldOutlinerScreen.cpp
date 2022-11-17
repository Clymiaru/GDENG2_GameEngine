#include "WorldOutlinerScreen.h"

#include <Engine/Core/Core.h>

#include "../Dependencies/ImGui/imgui.h"

#include <Engine/ECS/Core/Entity.h>
#include <Engine/UI/UISystem.h>

namespace Editor
{
	WorldOutlinerScreen::WorldOutlinerScreen(const Engine::ScreenID id)
		: AUIScreen{id, "World Outliner"}
	{}

	// WorldOutlinerPanel::WorldOutlinerPanel(Engine::List<Engine::Entity*>& entityRef) :
	// 	AUIScreen{"World Outliner"},
	// 	m_EntitiesRef{entityRef}
	// {
	// 	for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
	// 	{
	// 		m_SelectedEntities.push_back({i, false});
	// 	}
	// }

	WorldOutlinerScreen::~WorldOutlinerScreen()
	{
	}

	// Engine::Entity* WorldOutlinerPanel::GetSelectedEntity() const
	// {
	// 	for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
	// 	{
	// 		if (m_SelectedEntities[i].second == true)
	// 		{
	// 			return m_EntitiesRef[i];
	// 		}
	// 	}
	// 	return nullptr;
	// }

	// void WorldOutlinerPanel::DrawImpl()
	// {
	// 	for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
	// 	{
	// 		Engine::String entityLabel = m_EntitiesRef[i]->Name;
	// 		entityLabel += "##WorldOutlinerPanel";
	// 		ImGui::Selectable(entityLabel.c_str(), &m_SelectedEntities[i].second);
	// 	}
	// }

	void WorldOutlinerScreen::DrawImpl()
	{
		if (m_IsOpen)
		{
			ImGui::Begin(GetNameAndIDLabel(), &m_IsOpen);

			ImGui::Text("Placeholder");

			ImGui::End();
		}
		else
		{
			Engine::UISystem::Destroy(m_ID);
		}
		
	}
}

