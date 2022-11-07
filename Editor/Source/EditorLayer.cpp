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

#define Q1
#define Q2
#define Q3
#define Q4
#define Q5
#define Q6
#define Q7

#undef Q1
#undef Q5
#undef Q6
#undef Q7

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

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/RainbowColorShader.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/RainbowColorShader.hlsl");

		auto rainbowColorVS = ShaderLibrary::GetShaderRef<VertexShader>("RainbowColorShader");
		auto rainbowColorPS = ShaderLibrary::GetShaderRef<PixelShader>("RainbowColorShader");

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/WhiteColorShader.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/WhiteColorShader.hlsl");

		auto whiteColorVS = ShaderLibrary::GetShaderRef<VertexShader>("WhiteColorShader");
		auto whiteColorPS = ShaderLibrary::GetShaderRef<PixelShader>("WhiteColorShader");

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/Basic/TexturedShader.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/Basic/TexturedShader.hlsl");

		auto texturedVS = ShaderLibrary::GetShaderRef<VertexShader>("TexturedShader");
		auto texturedPS = ShaderLibrary::GetShaderRef<PixelShader>("TexturedShader");

#ifdef Q1
		{
			Entity* rotateWhiteAnimeCube            = new Entity("RotateAnimCube");
			rotateWhiteAnimeCube->Transform().Scale = Vector3Float(5.0f, 5.0f, 5.0f);
		
			rotateWhiteAnimeCube->Transform().Position = Vector3Float(0.0f, 0.0f, -0.0f);
			rotateWhiteAnimeCube->Transform().Rotation = Vector3Float(-0.0f, 0.0f, 0.0f);
		
			auto& renderComponent = rotateWhiteAnimeCube->AttachComponent<RenderComponent>(*rotateWhiteAnimeCube,
			                                                                               Primitive::RainbowCube(),
			                                                                               rainbowColorVS, rainbowColorPS);
			renderComponent.AlbedoColor = Color(1.0f, 1.0f, 1.0f);
			m_EntityList.push_back(rotateWhiteAnimeCube);
		}
#endif

#ifdef Q3
		{
			Entity* rotateWhiteAnimeCube            = new Entity("RotateAnimCube");
			rotateWhiteAnimeCube->Transform().Scale = Vector3Float(1.0f, 1.0f, 1.0f);

			rotateWhiteAnimeCube->Transform().Position = Vector3Float(0.0f, 0.0f, 0.0f);

			auto& renderComponent = rotateWhiteAnimeCube->AttachComponent<RenderComponent>(*rotateWhiteAnimeCube,
			                                                                               Primitive::RainbowCube(),
			                                                                               rainbowColorVS,
			                                                                               rainbowColorPS);
			renderComponent.AlbedoColor = Color(1.0f, 1.0f, 1.0f);
			m_EntityList.push_back(rotateWhiteAnimeCube);
		}
#endif
		// {
		// 	Entity* rotateWhiteAnimeCube            = new Entity("RotateAnimCube");
		// 	rotateWhiteAnimeCube->Transform().Scale = Vector3Float(20.0f, 20.0f, 20.0f);
		//
		// 	rotateWhiteAnimeCube->Transform().Position = Vector3Float(0.0f, 0.0f, -300.0f);
		// 	rotateWhiteAnimeCube->Transform().Rotation = Vector3Float(-20.0f, 25.0f, 0.0f);
		//
		// 	auto& renderComponent = rotateWhiteAnimeCube->AttachComponent<RenderComponent>(*rotateWhiteAnimeCube,
		// 	                                                                               Primitive::Cube(),
		// 	                                                                               whiteColorVS, whiteColorPS);
		// 	renderComponent.AlbedoColor = Color(1.0f, 1.0f, 1.0f);
		// 	m_EntityList.push_back(rotateWhiteAnimeCube);
		// }

		// {
		// 	for (int i = 0; i < 50; i++)
		// 	{
		// 		Entity* rotateWhiteAnimeCube               = new Entity("Rotate50Cube" + std::to_string(i));
		// 		rotateWhiteAnimeCube->Transform().Scale    = Vector3Float(15.0f, 15.0f, 15.0f);
		// 		rotateWhiteAnimeCube->Transform().Position = Vector3Float(Random::Range(-100.0f, 100.0f),
		// 		                                                          Random::Range(-100.0f, 100.0f),
		// 		                                                          Random::Range(-100.0f, 100.0f));
		//
		// 		auto& renderComponent = rotateWhiteAnimeCube->AttachComponent<RenderComponent>(*rotateWhiteAnimeCube,
		// 		                                                                               Primitive::Cube(),
		// 		                                                                               solidVS,
		// 		                                                                               solidPS);
		// 		renderComponent.AlbedoColor = Color(Random::Range(0.01f, 1.0f),
		// 		                                    Random::Range(0.01f, 1.0f),
		// 		                                    Random::Range(0.01f, 1.0f));
		// 		m_EntityList.push_back(rotateWhiteAnimeCube);
		// 	}
		// }
#ifdef Q5
		{
			Entity* warpingCubePlane            = new Entity("WarpAnimCube");
			warpingCubePlane->Transform().Scale = Vector3Float(10.0f, 10.0f, 10.0f);

			auto& renderComponent = warpingCubePlane->AttachComponent<RenderComponent>(*warpingCubePlane,
			                                                                           Primitive::Cube(),
			                                                                           whiteColorVS, whiteColorPS);
			renderComponent.AlbedoColor = Color(0.8f, 0.4f, 1.0f);
			m_EntityList.push_back(warpingCubePlane);
		}
#endif

#ifdef Q6

		{
			Entity* cube0               = new Entity("Cube0");
			cube0->Transform().Position = Vector3Float(0.0f, 0.9f, 0.0f);
			cube0->Transform().Scale = Vector3Float(1.0f, 1.0f, 1.0f);

			auto& rc = cube0->AttachComponent<RenderComponent>(*cube0,
			                                                   Primitive::Cube(),
			                                                   solidVS, solidPS);
			m_EntityList.push_back(cube0);
		}

		{
			Entity* cube1               = new Entity("Cube1");
			cube1->Transform().Position = Vector3Float(-1.5f, 2.0f, 0.0f);
			cube1->Transform().Scale = Vector3Float(1.0f, 1.0f, 1.0f);

			auto& rc = cube1->AttachComponent<RenderComponent>(*cube1,
			                                                   Primitive::Cube(),
			                                                   solidVS, solidPS);
			m_EntityList.push_back(cube1);
		}

		{
			Entity* cube2               = new Entity("Cube2");
			cube2->Transform().Position = Vector3Float(-1.5f, 3.0f, -2.0f);
			cube2->Transform().Scale = Vector3Float(1.0f, 1.0f, 1.0f);

			auto& rc = cube2->AttachComponent<RenderComponent>(*cube2,
			                                                   Primitive::Cube(),
			                                                   solidVS, solidPS);
			m_EntityList.push_back(cube2);
		}

		{
			Entity* plane               = new Entity("Plane");
			plane->Transform().Position = Vector3Float(0.0f, 0.0f, 0.0f);
			plane->Transform().Scale = Vector3Float(10.0f, 10.0f, 10.0f);

			auto& rc = plane->AttachComponent<RenderComponent>(*plane,
															   Primitive::Plane(),
															   solidVS, solidPS);
			m_EntityList.push_back(plane);
		}
#endif

#ifdef Q7
		auto createCardEntity = [&](const int id,
		                            const Vector3Float position) -> void
		{
			Entity* card               = new Entity("Card" + std::to_string(id));
			card->Transform().Scale    = Vector3Float(4.5f, 7.0f, 0.5f);
			card->Transform().Position = Vector3Float(position);

			auto& rc = card->AttachComponent<RenderComponent>(*card,
			                                                  Primitive::Cube(),
			                                                  solidVS, solidPS);
			rc.AlbedoColor = Color(0.8f, 0.4f, 1.0f);
			m_EntityList.push_back(card);
		};

		List<Vector3Float> cardPositions =
		{
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
			Vector3Float(0.0f, 0.0f, 0.0f),
		};

		for (int i = 0; i < 1; i++)
		{
			createCardEntity(i, cardPositions[i]);
		}
#endif
		// {
		// 	Entity* card1  = new Entity("Card1");
		// }
		//
		// 	Entity* card2  = new Entity("Card2");
		// 	Entity* card3  = new Entity("Card3");
		// 	Entity* card4  = new Entity("Card4");
		// 	Entity* card5  = new Entity("Card5");
		// 	Entity* card6  = new Entity("Card6");
		// 	Entity* card7  = new Entity("Card7");
		// 	Entity* card8  = new Entity("Card8");
		// 	Entity* card9  = new Entity("Card9");
		// 	Entity* card10 = new Entity("Card10");
		// 	Entity* card11 = new Entity("Card11");
		// 	Entity* card12 = new Entity("Card12");
		// 	Entity* card13 = new Entity("Card13");
		// 	Entity* card14 = new Entity("Card14");

		m_RenderQuad = CreateUniquePtr<RenderQuad>();

		m_CameraHandler.Initialize(2,
		                           List<Vector3Float>
		                           {
			                           Vector3Float(5.0f, 1.5f, -7.0),
			                           Vector3Float(0.0f, -500.0f, -400.0f),
		                           },
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 120.0f, 0),
			                           Vector3Float(270.0f, 90.0f, 0),
		                           });

		m_PostProcessHandler = CreateUniquePtr<PostProcessHandler>(3);
		m_PostProcessHandler->Start();

		m_PostProcessingPanel   = new PostProcessingPanel(*m_PostProcessHandler);
		m_WorldOutlinerPanel    = new WorldOutlinerPanel(m_EntityList);
		m_EntityPropertiesPanel = new EntityPropertiesPanel(*m_WorldOutlinerPanel, m_EntityList);
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
		m_CameraHandler.UpdateSceneCameraOfId(0);
		m_CameraHandler.GetSceneCamera(0).Transform().Rotation = Vector3Float(m_CameraRotation[0], m_CameraRotation[1],
		                                                                      m_CameraRotation[2]);
		m_CameraHandler.GetSceneCamera(0).Transform().Position = Vector3Float(m_CameraPosition[0], m_CameraPosition[1],
		                                                                      m_CameraPosition[2]);

#ifdef Q3
		const Vector3Float scaleA = Vector3Float(1.0f, 1.0f, 1.0f);
		const Vector3Float scaleB   = Vector3Float(0.25f, 0.25f, 0.25f);
		static float currentTime = 0.0f;
		currentTime += Application::DeltaTime() * 0.8f;
		for (int i = 0; i < m_EntityList.size(); i++)
		{
			auto* warpAnimCube = m_EntityList[i];

			float moveAmount = 2.0f * Application::DeltaTime();
			warpAnimCube->Transform().Position += Vector3Float(moveAmount, moveAmount, 0.0f);

			warpAnimCube->Transform().Scale = Vector3Float::Lerp(scaleA,
																 scaleB,
																 std::clamp(currentTime,
																			0.0f,
																			1.0f));
		}
#endif
		// for (int i = 0; i < m_EntityList.size(); i++)
		// {
		// 	if (m_EntityList[i]->Name == "RotateAnimCube")
		// 	{
		// 		auto* rotateCubeAnim = m_EntityList[i];
		// 		rotateCubeAnim->Transform().Rotation.x += Application::DeltaTime() * 500.0f;
		// 		rotateCubeAnim->Transform().Rotation.y += Application::DeltaTime() * 600.0f;
		// 		rotateCubeAnim->Transform().Rotation.z += Application::DeltaTime() * 700.0f;
		// 	}
		// }

		// for (int i = 0; i < m_EntityList.size(); i++)
		// {
		// 	auto* rotateCubeAnim = m_EntityList[i];
		// 	rotateCubeAnim->Transform().Rotation.x += Application::DeltaTime() * Random::Range(0.01f, 1.0f) * 500.0f;
		// 	rotateCubeAnim->Transform().Rotation.y += Application::DeltaTime() * Random::Range(0.01f, 1.0f) * 600.0f;
		// 	rotateCubeAnim->Transform().Rotation.z += Application::DeltaTime() * Random::Range(0.01f, 1.0f) * 700.0f;
		// }
#ifdef Q5
		const Vector3Float originalScale = Vector3Float(10.0f, 10.0f, 10.0f);
		const Vector3Float warpedScale   = Vector3Float(50.0f, 50.0f, 0.0f);
		static float currentTime = -0.2f;
		currentTime += Application::DeltaTime() * 0.5f;
		if (currentTime < 1.0f)
		{
			for (int i = 0; i < m_EntityList.size(); i++)
			{
				auto* warpAnimCube = m_EntityList[i];

				warpAnimCube->Transform().Scale = Vector3Float::Lerp(originalScale,
				                                                     warpedScale,
				                                                     std::clamp(currentTime,
				                                                                0.0f,
				                                                                1.0f));
			}
		}
#endif
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

		ImGui::Begin("Camera Controls");
		ImGui::DragFloat3("Camera Position", m_CameraPosition, 0.1f);
		ImGui::DragFloat3("Camera Rotation", m_CameraRotation, 0.1f);
		ImGui::End();

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
