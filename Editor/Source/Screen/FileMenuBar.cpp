#include "FileMenuBar.h"

#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/ECS/Entity/EmptyEntity.h>
#include <Engine/ECS/Entity/Camera.h>
#include <Engine/ECS/Entity/Capsule.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/EditorCamera.h>
#include <Engine/ECS/Entity/Plane.h>
#include <Engine/ECS/Entity/Sphere.h>
#include <Engine/ResourceManagement/Core/ResourceSystem.h>
#include <Engine/SceneManagement/SceneManager.h>

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
				if (ImGui::MenuItem("New Scene"))
				{
					Engine::SceneManager::CreateNewScene("New Scene");
					Engine::Debug::Log("New scene created!");
				}

				if (ImGui::MenuItem("Save Scene"))
				{
					Engine::SceneManager::SaveScene("Assets/Scenes/TestScene.level");
					Engine::Debug::Log("SceneName.level saved!");
				}

				if (ImGui::BeginMenu("Load Scene"))
				{
					// Show list of level files in the base directory (For now since expected files is not many)

					if (ImGui::MenuItem("Test.level"))
					{
						Engine::Debug::Log("SceneName.level loaded!");
						Engine::SceneManager::LoadSceneFromFile("Assets/Scenes/TestScene.level");
					}

					//ImGui::Begin()
					ImGui::EndMenu();
				}

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
						auto* entity = Engine::EntityManager::Create<Engine::Cube>("Cube");

						const auto staticMesh = entity->GetComponent<Engine::StaticMeshComponent>();
						const auto texture    = Engine::Application::GetResourceSystem().Get<
							Engine::TextureResource>("WhiteSquare");
						staticMesh->SetTexture(texture);
					}

					if (ImGui::MenuItem("Plane"))
					{
						auto* entity = Engine::EntityManager::Create<Engine::Plane>("Plane");

						const auto staticMesh = entity->GetComponent<Engine::StaticMeshComponent>();
						const auto texture    = Engine::Application::GetResourceSystem().Get<
							Engine::TextureResource>("WhiteSquare");
						staticMesh->SetTexture(texture);
					}

					if (ImGui::MenuItem("Sphere"))
					{
						auto* entity = Engine::EntityManager::Create<Engine::Sphere>("Sphere");

						const auto staticMesh = entity->GetComponent<Engine::StaticMeshComponent>();
						const auto texture    = Engine::Application::GetResourceSystem().Get<
							Engine::TextureResource>("WhiteSquare");
						staticMesh->SetTexture(texture);
					}

					if (ImGui::MenuItem("Capsule"))
					{
						auto* entity = Engine::EntityManager::Create<Engine::Capsule>("Capsule");

						const auto staticMesh = entity->GetComponent<Engine::StaticMeshComponent>();
						const auto texture    = Engine::Application::GetResourceSystem().Get<
							Engine::TextureResource>("WhiteSquare");
						staticMesh->SetTexture(texture);
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
					auto* editorCamera = Engine::EntityManager::Create<Engine::EditorCamera>("EditorCamera", 512UL,
					                                                                         512UL);
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
