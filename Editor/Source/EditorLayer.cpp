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
		m_ViewportFramebuffers{},
		m_EntityList{Engine::List<Engine::Cube*>()},
		m_Plane{nullptr},
		m_CameraHandler{3},
		m_CurrentSceneCamera{0}
	{
	}

	EditorLayer::~EditorLayer() = default;

	void EditorLayer::OnAttach()
	{
		// Initialize a new Scene or load an existing scene
		using namespace Engine;

		FramebufferProfile sceneFramebufferProfile;
		sceneFramebufferProfile.Width  = Application::WindowRect().Width;
		sceneFramebufferProfile.Height = Application::WindowRect().Height;
		
		for (int i = 0; i < 3; i ++)
		{
			m_ViewportFramebuffers.push_back(new Framebuffer(sceneFramebufferProfile));
		}

		ShaderLibrary::Register<VertexShader>("Assets/DefaultShader.hlsl",
		                                      "vsmain");

		ShaderLibrary::Register<PixelShader>("Assets/DefaultShader.hlsl",
		                                     "psmain");

		Cube* cubeEntity              = new Cube("Testing Entity", Vector3Float());
		cubeEntity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);
		m_EntityList.emplace_back(cubeEntity);

		m_Plane                       = new Plane("PlaneEntity", Vector3Float());
		m_Plane->Transform().Position = Vector3Float(0.0f, -5.0f, 0.0f);
		m_Plane->Transform().Scale    = Vector3Float(100.0f, 100.0f, 100.0f);

		m_CameraHandler.Initialize(3,
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 0, -400.0),
			                           Vector3Float(0.0f, -500.0f, -400.0f),
			                           Vector3Float(-100.0f, -400.0f, 300.0f)
		                           },
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 90.0f, 0),
			                           Vector3Float(60.0f, 90.0f, 0),
			                           Vector3Float(60.0f, -90.0f, 0)
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
		for (int i = 0 ; i < 3; i++)
		{
			m_ViewportFramebuffers[i]->ClearRenderTarget(Engine::Color{0.0f, 0.5f, 1.0f, 1.0f});
			m_ViewportFramebuffers[i]->ClearDepthStencil();
			Engine::Renderer::SetRenderTarget(&m_ViewportFramebuffers[i]->GetRenderTargetView(),
											  &m_ViewportFramebuffers[i]->GetDepthStencilView());

			for (auto* entity : m_EntityList)
			{
				entity->Draw(m_CameraHandler.GetSceneCamera(i));
			}
			m_Plane->Draw(m_CameraHandler.GetSceneCamera(i));
		}

		// TODO: Post-Processed Quad must be the last to be rendered
		// TODO: Last render target is the post-processed quad

		// Draw stuff
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

			if (ImGui::BeginMenu("Credits"))
			{
				showCredits = !showCredits;
				ImGui::EndMenu();
			}

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

		// const ImGuiViewport* viewport = ImGui::GetMainViewport();
		// ImGui::SetNextWindowPos(viewport->WorkPos);
		// ImGui::SetNextWindowSize(viewport->WorkSize);
		// ImGui::SetNextWindowViewport(viewport->ID);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		// ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		// window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		// window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("Testing");

		ImGui::Image(&m_ViewportFramebuffers[0]->GetShaderResourceView(), ImVec2(320, 180));
		ImGui::End();

		ImGui::Begin("Testing1");

		ImGui::Image(&m_ViewportFramebuffers[1]->GetShaderResourceView(), ImVec2(320, 180));
		ImGui::End();

		ImGui::Begin("Testing2");

		ImGui::Image(&m_ViewportFramebuffers[2]->GetShaderResourceView(), ImVec2(320, 180));
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
		for (int i = 0; i < 3; i++)
		{
			delete m_ViewportFramebuffers[i];
		}

		m_ViewportFramebuffers.clear();
		
		delete m_CreditsScreen;
	}
}
