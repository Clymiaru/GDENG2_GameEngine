#include "EditorLayer.h"

#include <Engine/Core/Application.h>
#include <Engine/ECS/Component/RenderComponent.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/Graphics/ShaderLibrary.h>
#include <Engine/Input/Input.h>

#include <Engine/ECS/Component/TransformComponent.h>

#include <Engine/Graphics/RenderQuad.h>

#include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
#include <Engine/Graphics/Primitives/Primitive.h>
#include <Engine/ImGui/ImGuiSystem.h>

#include <Utils/Random.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"

#include "Screen/EntityPropertiesPanel.h"
#include "Screen/PostProcessingPanel.h"
#include "Screen/WorldOutlinerPanel.h"

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{"EditorLayer"},
		m_EditorViewFramebuffer{nullptr},
		m_GameViewFramebuffer{nullptr},
		m_EntityList{Engine::List<Engine::Entity*>()},
		m_CameraHandler{2},
		m_RenderQuad{nullptr},
		m_PostProcessHandler{nullptr},
		m_CurrentSceneCamera{0},
		m_PostProcessingPanel{nullptr}
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

		auto solidVS = ShaderLibrary::GetShaderRef<VertexShader>("SolidColorShader");
		auto solidPS = ShaderLibrary::GetShaderRef<PixelShader>("SolidColorShader");

		// Object initialization
		for (int i = 0; i < 100; i++)
		{
			Entity* entity            = new Entity("Cube" + std::to_string(i));
			entity->Transform().Scale = Vector3Float(20.0f, 20.0f, 20.0f);

			entity->Transform().Position = Vector3Float(Random::Range(-200.0f, 200.0f),
			                                            Random::Range(-200.0f, 200.0f),
			                                            Random::Range(-200.0f, 200.0f));

			auto& renderComponent = entity->AttachComponent<RenderComponent>(*entity, Primitive::Cube(), solidVS,
			                                                                 solidPS);
			renderComponent.AlbedoColor = Color(Random::Range(0.1f, 0.9f),
			                                    Random::Range(0.1f, 0.9f),
			                                    Random::Range(0.1f, 0.9f));

			m_EntityList.push_back(entity);
		}

		for (int i = 0; i < 5; i++)
		{
			Entity* entity            = new Entity("Plane" + std::to_string(i));
			entity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);

			entity->Transform().Position = Vector3Float(0.0f,
			                                            -5.0f,
			                                            (i * 100.0f));

			auto& renderComponent = entity->AttachComponent<RenderComponent>(*entity, Primitive::Plane(), solidVS, solidPS);

			renderComponent.AlbedoColor = Color(Random::Range(0.1f, 0.9f),
												Random::Range(0.1f, 0.9f),
												Random::Range(0.1f, 0.9f));

			m_EntityList.push_back(entity);
		}

		for (int i = 0; i < 1; i++)
		{
			Entity* entity            = new Entity("Circle" + std::to_string(i));
			entity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);

			entity->Transform().Position = Vector3Float();

			auto& renderComponent = entity->AttachComponent<RenderComponent>(*entity, Primitive::Circle(5.0f, 32), solidVS, solidPS);

			renderComponent.AlbedoColor = Color(1.0f, 1.0f, 1.0f);

			m_EntityList.push_back(entity);
		}

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

		m_PostProcessingPanel = new PostProcessingPanel(*m_PostProcessHandler);
		m_WorldOutlinerPanel = new WorldOutlinerPanel(m_EntityList);
		m_EntityPropertiesPanel = new EntityPropertiesPanel(*m_WorldOutlinerPanel, m_EntityList);
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
		m_CameraHandler.UpdateSceneCameraOfId(0);
	}

	void EditorLayer::OnRender()
	{
		for (auto* entity : m_EntityList)
		{
			if (const auto* component = entity->GetComponent<Engine::RenderComponent>();
				component != nullptr)
			{
				component->Draw(m_CameraHandler.GetSceneCamera(0));
			}
		}

		auto* postProcessView = &m_PostProcessHandler->ProcessEffects(*m_Framebuffer);

		Engine::Renderer::StartRender(*m_EditorViewFramebuffer);
		m_RenderQuad->Draw(m_Framebuffer->GetFrame());
		Engine::Renderer::EndRender(*m_EditorViewFramebuffer);

		Engine::Renderer::StartRender(*m_GameViewFramebuffer);
		m_RenderQuad->Draw(*postProcessView);
		Engine::Renderer::EndRender(*m_GameViewFramebuffer);
	}

	void EditorLayer::OnImGuiRender()
	{
		using namespace Engine;
		// TODO: Resizing viewports
		ImGui::DockSpaceOverViewport();

		ImGuiSystem::ShowDemoWindow(true);

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

		m_WorldOutlinerPanel->Draw();

		m_EntityPropertiesPanel->Draw();

		m_PostProcessingPanel->Draw();

		ImGui::Begin("Scene View");
		ImGui::Image(&m_EditorViewFramebuffer->GetFrame(), ImVec2(16 * 60, 9 * 60));
		ImGui::End();

		ImGui::Begin("Game View");
		ImGui::Image(&m_GameViewFramebuffer->GetFrame(), ImVec2(16 * 60, 9 * 60));
		ImGui::End();
	}

	void EditorLayer::OnDetach()
	{
		delete m_PostProcessingPanel;
		delete m_EntityPropertiesPanel;
		delete m_WorldOutlinerPanel;
		
		for (auto i = 0; i < m_EntityList.size(); i++)
		{
			delete m_EntityList[i];
			m_EntityList[i] = nullptr;
		}

		m_CameraHandler.Terminate();

		
	}
}
