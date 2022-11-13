#include "WorldOutlinerPanel.h"

#include <Engine/Core/Core.h>

#include "../Dependencies/ImGui/imgui.h"

#include <Engine/ECS/Core/Entity.h>

namespace Editor
{
	WorldOutlinerPanel::WorldOutlinerPanel(Engine::List<Engine::Entity*>& entityRef) :
		AUIScreen{"World Outliner"},
		m_EntitiesRef{entityRef}
	{
		for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
		{
			m_SelectedEntities.push_back({i, false});
		}
	}

	WorldOutlinerPanel::~WorldOutlinerPanel()
	{
	}

	Engine::Entity* WorldOutlinerPanel::GetSelectedEntity() const
	{
		for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
		{
			if (m_SelectedEntities[i].second == true)
			{
				return m_EntitiesRef[i];
			}
		}
		return nullptr;
	}

	void WorldOutlinerPanel::DrawImpl()
	{
		for (int i = 0; i < (int)m_EntitiesRef.size(); i++)
		{
			Engine::String entityLabel = m_EntitiesRef[i]->Name;
			entityLabel += "##WorldOutlinerPanel";
			ImGui::Selectable(entityLabel.c_str(), &m_SelectedEntities[i].second);
		}
	}
}

