#include "FileMenuBar.h"

#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/ECS/Entity/EmptyEntity.h>
#include <Engine/ECS/Entity/Camera.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/EditorCamera.h>

#include <Engine/UI/UISystem.h>

#include "EntityInspectorScreen.h"
#include "EditorViewportScreen.h"
#include "GameViewportScreen.h"
#include "WorldOutlinerScreen.h"

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	FileMenuBar::FileMenuBar(Engine::ScreenID id,
	                         WorldOutlinerScreen& worldOutlinerScreenRef) :
		AUIScreen{id, "File Menu Bar"},
		m_WorldOutlinerScreenRef{worldOutlinerScreenRef} { }

	FileMenuBar::~FileMenuBar() = default;

	void FileMenuBar::DrawImpl()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::BeginMenu("Create Entity"))
				{
					if (ImGui::MenuItem("Empty"))
					{
						Engine::EntityManager::Create<Engine::EmptyEntity>();
					}

					if (ImGui::MenuItem("Game Camera"))
					{
						Engine::EntityManager::Create<Engine::Camera>("Game Camera", 512UL, 512UL);
					}

					if (ImGui::MenuItem("Cube"))
					{
						Engine::EntityManager::Create<Engine::Cube>("Cube");
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Inspector"))
				{
					Engine::UISystem::Create<EntityInspectorScreen>(m_WorldOutlinerScreenRef);
				}

				if (ImGui::MenuItem("Scene Viewport"))
				{
					auto* editorCamera = Engine::EntityManager::Create<Engine::EditorCamera>("EditorCamera", 512UL, 512UL);
					Engine::UISystem::Create<EditorViewportScreen>(editorCamera);
				}

				if (ImGui::MenuItem("Game Viewport"))
				{
					Engine::UISystem::Create<GameViewportScreen>();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Camera"))
			{
				if (ImGui::MenuItem("Align With View"))
				{
					using namespace Engine;
					// Get Current Editor Camera
					const auto currentEditorCamera = Application::GetComponentSystem()
					                                 .GetCameraSystem().GetEditorCamera(0);

					// Get Game Camera
					const auto gameCamera = Application::GetComponentSystem()
					                        .GetCameraSystem().GetGameCamera();

					// Game Camera Transform = EditorCamera Transform
					gameCamera->SetPosition(currentEditorCamera->GetPosition());
					gameCamera->SetRotation(currentEditorCamera->GetRotation());
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}
