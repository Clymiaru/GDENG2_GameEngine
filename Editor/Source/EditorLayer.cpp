#include "EditorLayer.h"

#include <Engine/Core/Application.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/Graphics/ShaderLibrary.h>
#include <Engine/Input/Input.h>

#include <Engine/ECS/Component/TransformComponent.h>

#include <Engine/Graphics/RenderQuad.h>

#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/Plane.h>

#include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
#include <Engine/Graphics/PostProcessEffect/SimpleChromaticAberrationPostProcessEffect.h>
#include <Engine/Graphics/PostProcessEffect/VignettePostProcessEffect.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{"EditorLayer"},
		m_EditorViewFramebuffer{nullptr},
		m_GameViewFramebuffer{nullptr},
		m_EntityList{Engine::List<Engine::Cube*>()},
		m_Plane{nullptr},
		m_CameraHandler{2},
		m_RenderQuad{nullptr},
		m_PostProcessHandler{nullptr},
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

		m_Framebuffer           = CreateUniquePtr<Framebuffer>(sceneFramebufferProfile, Renderer::GetDevice());
		m_EditorViewFramebuffer = CreateUniquePtr<Framebuffer>(sceneFramebufferProfile, Renderer::GetDevice());
		m_GameViewFramebuffer   = CreateUniquePtr<Framebuffer>(sceneFramebufferProfile, Renderer::GetDevice());

		// Shader initialization (AUTOMATE?)
		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");

		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/SolidColorShader.hlsl");

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/RenderTarget/RenderQuad_VS.hlsl");

		ShaderLibrary::Register<PixelShader>("Assets/Shaders/RenderTarget/RenderQuad_PS.hlsl");

		// Object initialization
		Cube* cubeEntity = new Cube("CubeEntity");

		cubeEntity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);
		m_EntityList.push_back(cubeEntity);

		m_Plane = new Plane("PlaneEntity");

		m_Plane->Transform().Position = Vector3Float(0.0f, -5.0f, 0.0f);
		m_Plane->Transform().Scale    = Vector3Float(100.0f, 100.0f, 100.0f);

		m_RenderQuad = CreateUniquePtr<RenderQuad>();

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

		m_PostProcessHandler = CreateUniquePtr<PostProcessHandler>(3);
		m_PostProcessHandler->Start();

		m_PostProcessHandler->AddEffect(new VignettePostProcessEffect({
			                                                              Color(0.5f, 0.0f, 0.2f, 1.0f),
			                                                              Vector2Float(1.0f, 0.0f),
			                                                              Vector2Float(Application::WindowRect().Width,
			                                                                           Application::WindowRect().Height)
		                                                              }));

		m_ChromaticEffectID = m_PostProcessHandler->AddEffect(new SimpleChromaticAberrationPostProcessEffect({
			                                                                                                     Vector2Float(Application::WindowRect()
			                                                                                                                  .Width,
			                                                                                                                  Application::WindowRect()
			                                                                                                                  .Height),
			                                                                                                     Vector2Float(-1.0f,
			                                                                                                                  1.0f)
		                                                                                                     }));
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
		Vector2Float mousePosition = Vector2Float((float)Input::Mouse().DeltaMousePosition.x,
		                                          (float)Input::Mouse().DeltaMousePosition.y);
		mousePosition.Normalize();

		SimpleChromaticAberrationEffectData* chromaticEffectData =
				new SimpleChromaticAberrationEffectData(Vector2Float(Application::WindowRect().Width,
				                                                     Application::WindowRect().Height),
				                                        mousePosition);

		m_PostProcessHandler->UpdateEffectData(m_ChromaticEffectID, chromaticEffectData);
		m_CameraHandler.UpdateSceneCameraOfId(0);
	}

	void EditorLayer::OnRender()
	{
		for (auto* entity : m_EntityList)
		{
			entity->Draw(m_CameraHandler.GetSceneCamera(0));
		}
		m_Plane->Draw(m_CameraHandler.GetSceneCamera(0));

		// Post Process that requires previous frame goes like this
		// Post Process that do not require previous frame might need multiple RTV or
		// draw multiple quads at the same time

		auto* postProcessView = &m_PostProcessHandler->ProcessEffects(*m_Framebuffer);

		Engine::Renderer::StartRender(*m_EditorViewFramebuffer);
		m_RenderQuad->Draw(*postProcessView);
		Engine::Renderer::EndRender(*m_EditorViewFramebuffer);

		Engine::Renderer::StartRender(*m_GameViewFramebuffer);
		m_RenderQuad->Draw(*postProcessView);
		Engine::Renderer::EndRender(*m_GameViewFramebuffer);
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
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Create Entity"))
				{
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

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
	}
}
