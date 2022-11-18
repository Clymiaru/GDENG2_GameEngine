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
		m_WorldOutlinerScreenRef{worldOutlinerScreenRef}
	{
		Engine::EntityManager::ListenToDestroyEvent([this](const Engine::EntityID entityID,
		                                                   const Engine::StringView entityName) -> void
		{
			OnEntityDestroy(entityID, entityName);
		});
		
	}

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

			Entity* selectedEntity = EntityManager::GetEntity(m_CurrentEntityID);

			if (selectedEntity == nullptr)
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

			ImGui::SameLine();

			String deleteButtonLabel = std::vformat("Delete##{0}{1}", std::make_format_args(m_Name, m_ID));
			if (ImGui::Button(deleteButtonLabel.c_str()))
			{
				m_IsDeletingObject = true;
			}

			ImGui::Checkbox("##Active", &selectedEntity->Active);

			ImGui::SameLine();

			ImGui::Text(selectedEntity->GetName().c_str());

			ImGui::Spacing();

			const auto componentList = EntityManager::GetAllComponentsOfEntity(selectedEntity->GetID());

			DrawComponents(selectedEntity, componentList);

			String popupLabel = std::vformat("AddComponentPopup##{0}{1}", std::make_format_args(m_Name, m_ID));
			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup(popupLabel.c_str());
			}
			
			if (ImGui::BeginPopup(popupLabel.c_str()))
			{
				ImGui::Text("Components");
				ImGui::Separator();
				for (size_t i = 0ULL; i < m_ComponentList.size(); i++)
				{
					if (ImGui::Selectable(m_ComponentList[i].c_str()))
					{
						// TODO: Don't make add component's selectable on components already added
						// TODO: May refactor to a function
						
						if (m_ComponentList[i] == "Transform")
						{
							selectedEntity->AttachComponent<TransformComponent>();
						}

						if (m_ComponentList[i] == "Render")
						{
							selectedEntity->AttachComponent<RenderComponent>();
						}
					}
				}
					
				ImGui::EndPopup();
			}
			

			ImGui::End();

			if (m_IsDeletingObject)
			{
				Reset();
				EntityManager::Destroy(selectedEntity);
			}
		}
		else
		{
			UISystem::Destroy(GetID());
		}
	}
	void EntityInspectorScreen::Reset()
	{
		m_IsLocked         = false;
		m_CurrentEntityID  = 0;
		m_IsDeletingObject = false;
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

	void EntityInspectorScreen::OnEntityDestroy(Engine::EntityID entityID, Engine::StringView entityName)
	{
		Reset();
	}
}
