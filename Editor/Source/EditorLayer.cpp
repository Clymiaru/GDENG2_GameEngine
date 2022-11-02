#include "EditorLayer.h"

#include <Engine/Graphics/Renderer.h>
#include <Engine/SceneManagement/Scene.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Goal for today
// Create a game object

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{L"EditorLayer"}
	{
	}

	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		// Initialize a new Scene or load an existing scene
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
	}

	void EditorLayer::OnRender()
	{
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// New Scene
				
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				// Create Entity
				// More options:
				// Empty Entity
				// Cube Entity
				// Plane Entity
				
				// if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				// if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				// ImGui::Separator();
				// if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				// if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				// if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// const ImGuiViewport* viewport = ImGui::GetMainViewport();
		// ImGui::SetNextWindowPos(viewport->WorkPos);
		// ImGui::SetNextWindowSize(viewport->WorkSize);
		// ImGui::SetNextWindowViewport(viewport->ID);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		// window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		// window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		//

		ImGui::DockSpaceOverViewport();

		ImGui::Begin("Testing");
		
		ImGui::End();
	}

	void EditorLayer::OnDetach()
	{
		// Unload scenes
		delete m_ActiveScene;
	}

}
