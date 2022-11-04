#include "EditorLayer.h"

#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/Plane.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/SceneManagement/Scene.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Goal for today
// Framebuffer and Viewport issue

// UI Screens and Manager
// Create game objects through the editor
// Display heirarchy

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{"EditorLayer"},
		m_CreditsScreen(new CreditsScreen()),
		m_EditorViewFramebuffer{nullptr},
		m_GameViewFramebuffer{nullptr},
		m_EntityList{Engine::List<Engine::Cube*>()},
		m_Plane{nullptr},
		m_CameraHandler{2},
		m_PostProcessQuad{nullptr},
		m_CurrentSceneCamera{0}
	{
	}

	EditorLayer::~EditorLayer() = default;

	void EditorLayer::OnAttach()
	{
		// Initialize a new Scene or load an existing scene
		using namespace Engine;

		// View initialization
		FramebufferProfile sceneFramebufferProfile;
		sceneFramebufferProfile.Width  = Application::WindowRect().Width;
		sceneFramebufferProfile.Height = Application::WindowRect().Height;

		m_EditorViewFramebuffer = new Framebuffer(sceneFramebufferProfile);
		m_GameViewFramebuffer   = new Framebuffer(sceneFramebufferProfile);

		// Shader initialization
		ShaderLibrary::Register<VertexShader>("Assets/DefaultShader.hlsl",
		                                      "vsmain");

		ShaderLibrary::Register<PixelShader>("Assets/DefaultShader.hlsl",
		                                     "psmain");

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/PostProcessFullscreenEffects/PostProcessSimpleChromaticAberration.hlsl",
		                                      "vsmain");

		ShaderLibrary::Register<PixelShader>("Assets/Shaders/PostProcessFullscreenEffects/PostProcessSimpleChromaticAberration.hlsl",
		                                     "psmain");

		// Object initialization
		Cube* cubeEntity              = new Cube("Testing Entity", Vector3Float());
		cubeEntity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);
		m_EntityList.emplace_back(cubeEntity);

		m_Plane                       = new Plane("PlaneEntity", Vector3Float());
		m_Plane->Transform().Position = Vector3Float(0.0f, -5.0f, 0.0f);
		m_Plane->Transform().Scale    = Vector3Float(100.0f, 100.0f, 100.0f);

		m_PostProcessQuad = new PostProcessQuad();

		m_CameraHandler.Initialize(2,
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 0, -400.0),
			                           Vector3Float(0.0f, -500.0f, -400.0f),
		                           },
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 90.0f, 0),
			                           Vector3Float(60.0f, 90.0f, 0),
		                           });
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
		m_CameraHandler.UpdateSceneCameraOfId(0);
	}

	void EditorLayer::OnRender()
	{
		m_EditorViewFramebuffer->Clear(Engine::Color{0.0f, 0.5f, 1.0f, 1.0f});
		m_EditorViewFramebuffer->SetAsRenderTarget();

		for (auto* entity : m_EntityList)
		{
			entity->Draw(m_CameraHandler.GetSceneCamera(0));
		}
		m_Plane->Draw(m_CameraHandler.GetSceneCamera(0));

		// Apply Post processing to EditorView-----
		// Get Texture from the Framebuffer to the quad.


		m_GameViewFramebuffer->Clear(Engine::Color{0.0f, 0.5f, 1.0f, 1.0f});
		m_GameViewFramebuffer->SetAsRenderTarget();

		m_PostProcessQuad->UpdateFrameRef(&m_EditorViewFramebuffer->GetFrame());
		m_PostProcessQuad->Draw();

		// for (auto* entity : m_EntityList)
		// {
		// 	entity->Draw(m_CameraHandler.GetSceneCamera(1));
		// }
		// m_Plane->Draw(m_CameraHandler.GetSceneCamera(1));

		// Apply Post processing to GameView

		// TODO: Post-Processed Quad must be the last to be rendered
		// TODO: Last render target is the post-processed quad
	}

	void EditorLayer::OnImGuiRender()
	{
		// TODO: Resizing viewports
		ImGui::DockSpaceOverViewport();

		static bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);

		static bool showCredits = false;

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

				if (ImGui::MenuItem("Create Entity"))
				{
				}

				// ImGui::Separator();
				// if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				// if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				// if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}

			// if (ImGui::Button("Credits##Button"))
			// {
			// 	showCredits = !showCredits;
			// }

			// if (ImGui::BeginMenu("Credits"))
			// {
			// 	showCredits = !showCredits;
			// 	ImGui::EndMenu();
			// }

			ImGui::EndMainMenuBar();
		}

		// if (showCredits)
		// {
		// 	ImGui::Begin("Credits");
		// 	ImGui::Text("Developer: Lanz Santiago");
		// 	ImGui::Text("Acknowlwedgements");
		// 	ImGui::End();
		// }

		m_CreditsScreen->DrawImpl();

		ImGui::Begin("World Outliner");
		ImGui::Text("World Outliner Placeholder");
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::Text("Properties Placeholder");
		ImGui::End();

		ImGui::Begin("Scene View");
		ImGui::Image(&m_EditorViewFramebuffer->GetFrame(), ImVec2(16 * 15, 9 * 15));
		ImGui::End();

		ImGui::Begin("Game View");
		ImGui::Image(&m_GameViewFramebuffer->GetFrame(), ImVec2(16 * 40, 9 * 40));
		ImGui::End();
	}

	void EditorLayer::OnDetach()
	{
		// Unload scenes
		for (auto i = 0; i < m_EntityList.size(); i++)
		{
			delete m_EntityList[i];
			m_EntityList[i] = nullptr;
		}
		delete m_Plane;

		m_EntityList.clear();

		m_CameraHandler.Terminate();

		//delete m_ActiveScene;

		delete m_PostProcessQuad;
		
		delete m_EditorViewFramebuffer;
		delete m_GameViewFramebuffer;

		delete m_CreditsScreen;
	}
}
