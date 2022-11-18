#include "EntityInspectorScreen.h"
#include <format>

#include <Engine/Core/Core.h>
#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Core/Entity.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/UI/UISystem.h>

#include "../Dependencies/ImGui/imgui.h"

namespace Editor
{
	EntityInspectorScreen::EntityInspectorScreen(Engine::ScreenID id, WorldOutlinerScreen& worldOutlinerScreenRef) :
		AUIScreen{id, "Inspector"},
		m_WorldOutlinerScreenRef{worldOutlinerScreenRef} { }

	EntityInspectorScreen::~EntityInspectorScreen() { }

	void EntityInspectorScreen::DrawImpl()
	{
		using namespace Engine;

		if (m_IsOpen)
		{
			ImGui::Begin(GetNameAndIDLabel(), &m_IsOpen);

			if (!m_IsLocked)
			{
				m_CurrentEntityID = m_WorldOutlinerScreenRef.GetSelectedEntityID();
			}

			// EntityID of 0 is guaranteed to be not an entity
			if (m_CurrentEntityID == InvalidEntity)
			{
				ImGui::End();
				return;
			}

			String lockButtonLabel;
			if (!m_IsLocked)
			{
				lockButtonLabel = std::vformat("Lock##{0}{1}", std::make_format_args(m_Name, m_ID));
				if (ImGui::Button(lockButtonLabel.c_str()))
				{
					m_IsLocked = true;
				}
			}
			else
			{
				lockButtonLabel = std::vformat("Unlock##{0}{1}", std::make_format_args(m_Name, m_ID));
				if (ImGui::Button(lockButtonLabel.c_str()))
				{
					m_IsLocked = false;
				}
			}

			Entity* selectedEntity = EntityManager::GetEntity(m_CurrentEntityID);

			ImGui::Checkbox("##Active", &selectedEntity->Active);

			ImGui::SameLine();

			ImGui::Text(selectedEntity->GetName().c_str());

			ImGui::Spacing();
		
			const auto componentList = EntityManager::GetAllComponentsOfEntity(selectedEntity->GetID());

			DrawComponents(selectedEntity, componentList);

			ImGui::End();
		}
		else
		{
			UISystem::Destroy(GetID());
		}
		
	}

	void EntityInspectorScreen::DrawComponents(const Engine::Entity* selectedEntity,
	                                           Engine::List<Engine::AComponent*> componentList)
	{
		using namespace Engine;
		const String entityNameID = std::vformat("{0}{1}",
		                                         std::make_format_args(selectedEntity->GetName(),
		                                                               selectedEntity->GetID()));

		for (const auto* component : componentList)
		{
			if (component->GetName() == "Transform")
			{
				DrawTransform(entityNameID, (TransformComponent*)component);
			}

			if (component->GetName() == "Render")
			{
				DrawRender(entityNameID, (RenderComponent*)component);
			}
		}
	}

	void EntityInspectorScreen::DrawTransform(Engine::StringView entityNameID,
	                                          Engine::TransformComponent* transform) const
	{
		using namespace Engine;
		if (ImGui::CollapsingHeader("Transform Component"))
		{
			const String entityPositionLabel = std::vformat("Position##Transform{0}",
			                                                std::make_format_args(entityNameID));
			ImGui::DragFloat3(entityPositionLabel.c_str(), (float*)&transform->Position, 0.1f);

			const String entityScaleLabel = std::vformat("Scale##Transform{0}",
			                                             std::make_format_args(entityNameID));
			ImGui::DragFloat3(entityScaleLabel.c_str(), (float*)&transform->Scale, 0.1f);

			const String entityRotationLabel = std::vformat("Rotation##Transform{0}",
			                                                std::make_format_args(entityNameID));
			ImGui::DragFloat3(entityRotationLabel.c_str(), (float*)&transform->Rotation, 0.1f);
		}
	}

	void EntityInspectorScreen::DrawRender(Engine::StringView entityNameID,
	                                       Engine::RenderComponent* render) const
	{
		using namespace Engine;
		if (ImGui::CollapsingHeader("Render Component"))
		{
			ImGui::Text("Render Options");
		}
	}
}
