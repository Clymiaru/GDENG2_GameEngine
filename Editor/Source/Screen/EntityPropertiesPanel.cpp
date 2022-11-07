#include "EntityPropertiesPanel.h"

#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Core/Entity.h>

#include "WorldOutlinerPanel.h"

#include "../Dependencies/ImGui/imgui.h"

namespace Editor
{
	EntityPropertiesPanel::EntityPropertiesPanel(WorldOutlinerPanel& worldOutlinerPanel,
	                                             Engine::List<Engine::Entity*>& entityRef) :
		AUIPanel{"Entity Inspector"},
		m_WorldOutlinerPanelRef{worldOutlinerPanel},
		m_EntityRef{entityRef}
		
	{
	}

	EntityPropertiesPanel::~EntityPropertiesPanel()
	{
	}

	void EntityPropertiesPanel::DrawImpl()
	{
		const Engine::Entity* selectedEntity = m_WorldOutlinerPanelRef.GetSelectedEntity();

		if (selectedEntity == nullptr)
		{
			ImGui::Text("No Entity Selected");
			return;
		}

		ImGui::Text(selectedEntity->Name.c_str());

		Engine::String entityPositionLabel = "Position";
		entityPositionLabel += "##EntityProperty";
		entityPositionLabel += selectedEntity->Name;
		ImGui::DragFloat3(entityPositionLabel.c_str(), (float*)&selectedEntity->Transform().Position, 0.1f);

		Engine::String entityScaleLabel = "Scale";
		entityScaleLabel += "##EntityProperty";
		entityScaleLabel += selectedEntity->Name;
		ImGui::DragFloat3(entityScaleLabel.c_str(), (float*)&selectedEntity->Transform().Scale, 0.1f);

		Engine::String entityRotationLabel = "Rotation";
		entityRotationLabel += "##EntityProperty";
		entityRotationLabel += selectedEntity->Name;
		ImGui::DragFloat3(entityRotationLabel.c_str(), (float*)&selectedEntity->Transform().Rotation, 0.1f);
	}
}
