#include "EntityInspectorScreen.h"
#include <format>

#include <Engine/Core/Core.h>
#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Component/Render/StaticMeshComponent.h>
#include <Engine/ECS/Core/Entity.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/ResourceManagement/Core/ResourceSystem.h>
#include <Engine/UI/UISystem.h>

#include "../Dependencies/ImGui/imgui.h"

namespace Editor
{
	EntityInspectorScreen::EntityInspectorScreen(Engine::ScreenID id, WorldOutlinerScreen& worldOutlinerScreenRef) :
		AUIScreen{id, "Inspector"},
		m_WorldOutlinerScreenRef{worldOutlinerScreenRef}
	{
		using namespace Engine;

		auto destroyEntityCallback = [this](const Entity* entity) { OnEntityDestroy(entity); };
		EntityManager::ListenToEntityDestroyEvent(destroyEntityCallback);
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

			// TODO: Adding components during runtime
			// String popupLabel = std::vformat("AddComponentPopup##{0}{1}", std::make_format_args(m_Name, m_ID));
			// if (ImGui::Button("Add Component"))
			// {
			// 	ImGui::OpenPopup(popupLabel.c_str());
			// }
			//
			// if (ImGui::BeginPopup(popupLabel.c_str()))
			// {
			// 	ImGui::Text("Components");
			// 	ImGui::Separator();
			// 	for (size_t i = 0ULL; i < m_ComponentList.size(); i++)
			// 	{
			// 		if (ImGui::Selectable(m_ComponentList[i].c_str()))
			// 		{
			// 			// TODO: Don't make add component's selectable on components already added
			// 			// TODO: May refactor to a function
			//
			// 			if (m_ComponentList[i] == "Transform")
			// 			{
			// 				selectedEntity->AttachComponent<TransformComponent>();
			// 			}
			//
			// 			// if (m_ComponentList[i] == "Render")
			// 			// {
			// 			// 	// TODO: Determine what to do for components that need parameters
			// 			// 	// Might need defaults
			// 			// 	selectedEntity->AttachComponent<RenderComponent>();
			// 			// }
			// 		}
			// 	}
			// 	ImGui::EndPopup();
			// }

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
	                                           Engine::List<Engine::SharedPtr<Engine::AComponent>> componentList)
	{
		using namespace Engine;
		const String entityNameID = std::vformat("{0}{1}",
		                                         std::make_format_args(selectedEntity->GetName(),
		                                                               selectedEntity->GetID()));

		for (const auto component : componentList)
		{
			if (component->GetName() == "Transform")
			{
				DrawTransform(entityNameID, std::dynamic_pointer_cast<TransformComponent>(component));
			}

			if (component->GetName() == "StaticMesh")
			{
				DrawStaticMesh(entityNameID, std::dynamic_pointer_cast<StaticMeshComponent>(component));
			}

			if (component->GetName() == "Camera")
			{
				DrawCamera(entityNameID, std::dynamic_pointer_cast<CameraComponent>(component));
			}
		}
	}

	void EntityInspectorScreen::DrawTransform(Engine::StringView entityNameID,
	                                          Engine::SharedPtr<Engine::TransformComponent> transform) const
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

	void EntityInspectorScreen::DrawStaticMesh(Engine::StringView entityNameID,
	                                       Engine::SharedPtr<Engine::StaticMeshComponent> render) const
	{
		using namespace Engine;
		if (ImGui::CollapsingHeader("Static Mesh Component"))
		{
			ImGui::Text("Render Options");
			const String entityAlbedoColor = std::vformat("Albedo Color##Render{0}",
			                                              std::make_format_args(entityNameID));
			ImGui::ColorEdit4(entityAlbedoColor.c_str(), (float*)&render->AlbedoColor);

			// TODO: Must able to change to any texture that is loaded.
			const String buttonSetBrick = std::vformat("Set Brick Texture##Render{0}",
			                                           std::make_format_args(entityNameID));
			if (ImGui::Button(buttonSetBrick.c_str()))
			{
				const auto texture = Application::GetResourceSystem().Get<TextureResource>("Brick1024x1024");
				render->SetTexture(texture);
			}

			const String buttonSetShiori = std::vformat("Set Shiori Texture##Render{0}",
			                                            std::make_format_args(entityNameID));
			if (ImGui::Button(buttonSetShiori.c_str()))
			{
				const auto texture = Application::GetResourceSystem().Get<TextureResource>("image0-42");
				render->SetTexture(texture);
			}

			const String buttonRemoveTexture = std::vformat("Remove Texture##Render{0}",
			                                                std::make_format_args(entityNameID));
			if (ImGui::Button(buttonRemoveTexture.c_str()))
			{
				render->RemoveTexture();
			}
		}
	}


	void EntityInspectorScreen::DrawCamera(Engine::StringView entityNameID,
	                                       Engine::SharedPtr<Engine::CameraComponent> camera) const
	{
		using namespace Engine;
		if (ImGui::CollapsingHeader("Camera Component"))
		{
			// Camera Clear Color
			const String cameraClearColor = std::vformat("Clear Color##Camera{0}",
			                                             std::make_format_args(entityNameID));
			ImGui::ColorEdit4(cameraClearColor.c_str(), (float*)camera->ClearColor);

			// Camera Projection
			int projectionMode = (int)camera->Projection;
			ImGui::Combo("Projection", &projectionMode, "Perspective\0Orthographic\0");

			if (projectionMode == 0)
			{
				camera->Projection = CameraComponent::Projection::Perspective;
			}
			if (projectionMode == 1)
			{
				camera->Projection = CameraComponent::Projection::Orthographic;
			}

			// If Camera Projection is Perspective
			if (camera->Projection == CameraComponent::Projection::Perspective)
			{
				// Camera FoV
				const String cameraFoV = std::vformat("FoV##Camera{0}",
				                                      std::make_format_args(entityNameID));
				ImGui::DragFloat(cameraFoV.c_str(), &camera->FoV, 0.1f, 0.1f, 180.0f);
			}

			// If Camera Projection is Orthographic
			if (camera->Projection == CameraComponent::Projection::Orthographic)
			{
				// Camera Size
				const String cameraOrthographicSize = std::vformat("Orthographic Size##Camera{0}",
				                                                   std::make_format_args(entityNameID));
				ImGui::DragFloat(cameraOrthographicSize.c_str(),
				                 &camera->OrthographicSize, 0.1f, 0.1f, 100.0f);
			}

			// Clipping Planes
			const String cameraNearClipPlane = std::vformat("Near Clip Plane##Camera{0}",
			                                                std::make_format_args(entityNameID));
			ImGui::DragFloat(cameraNearClipPlane.c_str(),
			                 &camera->NearClipPlane, 0.1f, 0.01f, 100000.0f);

			const String cameraFarClipPlane = std::vformat("Far Clip Plane##Camera{0}",
			                                               std::make_format_args(entityNameID));
			ImGui::DragFloat(cameraFarClipPlane.c_str(),
			                 &camera->FarClipPlane, 0.1f, 0.01f, 100000.0f);
		}
	}

	void EntityInspectorScreen::OnEntityDestroy(const Engine::Entity* entity)
	{
		Reset();
	}
}
