#include "SandboxLayer.h"

#include <Engine/ECS/Component/RenderComponent.h>
#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/Input/Input.h>
#include <Engine/SceneManagement/EditorSceneCamera.h>

#include "Engine/ECS/Entity/Entity.h"
#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Rendering System
// TODO: Camera
// TODO: Goal: Render 3 Cubes with Camera Movement

namespace Sandbox
{
	SandboxLayer::SandboxLayer() :
		Layer{L"SandboxLayer"},
		m_EntityList{Engine::List<Engine::Cube*>()},
		m_CameraHandler{3}
	{
	}

	SandboxLayer::~SandboxLayer() = default;

	void SandboxLayer::OnAttach()
	{
		using namespace Engine;
		ShaderLibrary::Register<VertexShader>(L"Assets/DefaultShader.hlsl",
		                                      "vsmain");

		ShaderLibrary::Register<PixelShader>(L"Assets/DefaultShader.hlsl",
		                                     "psmain");

		Cube* cubeEntity              = new Cube(L"Testing Entity", Vector3Float());
		cubeEntity->Transform().Scale = Vector3Float(100.0f, 100.0f, 100.0f);
		m_EntityList.emplace_back(cubeEntity);

		// Initialize Scene Cameras
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

		// // Object initialization
		// m_Plane = CreateUniquePtr<Plane>(Vector3Float(0,0,0), Vector3Float(500, 500.0f, 500), L"DefaultShader");
		//
		// m_TestCube = CreateUniquePtr<Cube>(Vector3Float(0,
		//                                            0,
		//                                            0),
		//                                    Vector3Float(50,
		//                                            50,
		//                                            50),
		//                                    L"DefaultShader");
		//
	}

	void SandboxLayer::OnUpdate()
	{
		m_Frame++;
		m_Timer += (float)Engine::Application::DeltaTime();

		if (m_Timer > 60.0f)
		{
			m_Fps   = (float)m_Frame / (m_Timer / 1000.0f);
			m_Frame = 0;
			m_Timer = 0.0f;
		}

		m_CameraHandler.UpdateSceneCameraOfId(m_CurrentSceneCamera);
	}

	void SandboxLayer::OnRender()
	{
		// FOR TEST RENDERING SYSTEM

		for (auto* entity : m_EntityList)
		{
			entity->Draw(m_CameraHandler.GetSceneCamera(m_CurrentSceneCamera));
		}

		// Scene Showcase
		// Input System and Camera (Scene can be traversed using keyboard and mouse)
		// Primitives (Cube, Capsules, Cylinder, Spheres, Planes)
		// Object Transforms
		// Basic SHaders
		// Depth Buffer and Perspective View
	}

	void SandboxLayer::OnImGuiRender()
	{
		ImGui::ShowDemoWindow(&m_IsDemoWindowOpen);

		ImGui::Begin("Viewport");

		ImGui::Text("Testing debug");

		for (auto* entity : m_EntityList)
		{
			std::basic_string toString = entity->Name();
			ImGui::Text("%ws", toString.c_str());

			auto entityPosition = (float*)entity->Transform().Position;

			ImGui::DragFloat3("Position", entityPosition);

			//entity->Transform().Position(Engine::Vector3Float(entityPosition[0], entityPosition[1], entityPosition[2]));

			auto entityScale = (float*)entity->Transform().Scale;
			ImGui::DragFloat3("Scale", entityScale);

			//entity->Transform().Scale(Engine::Vector3Float(entityScale[0], entityScale[1], entityScale[2]));

			auto entityRotation = (float*)entity->Transform().Rotation;
			ImGui::DragFloat3("Rotation", entityRotation);

			//entity->Transform().Rotation(Engine::Vector3Float(entityRotation[0], entityRotation[1], entityRotation[2]));
		}

		ImGui::Text("FPS: %f", m_Fps);
		ImGui::Text("Key Event Status");
		Engine::KeyboardInput keyInput = Engine::Input::Keyboard();
		ImGui::Text("Key Pressed: %c", (char)keyInput.KeyCode);
		ImGui::Text("Key State: %s", KeyStateToString(keyInput.KeyState).c_str());

		ImGui::Spacing();

		Engine::MouseInput mouseInput = Engine::Input::Mouse();
		ImGui::Text("Mouse Event Status");
		ImGui::Text("Mouse Position: %i, %i", mouseInput.MousePosition.x, mouseInput.MousePosition.y);
		ImGui::Text("Mouse Button: %s", MouseButtonToString(mouseInput.Button).c_str());
		ImGui::Text("Mouse State: %s", MouseStateToString(mouseInput.State).c_str());
		ImGui::Text("Delta Mouse Position: %i, %i", mouseInput.DeltaMousePosition.x,
		            mouseInput.DeltaMousePosition.y);

		ImGui::Spacing();

		ImGui::Text("Scene Cameras");


		if (ImGui::Button("Camera 0"))
		{
			m_CurrentSceneCamera = 0;
		}
		ImGui::SameLine();

		if (ImGui::Button("Camera 1"))
		{
			m_CurrentSceneCamera = 1;
		}
		ImGui::SameLine();

		if (ImGui::Button("Camera 2"))
		{
			m_CurrentSceneCamera = 2;
		}

		for (auto i = 0; i < 3; i++)
		{
			std::string cameraId = "Camera" + std::to_string(i);

			ImGui::Text((cameraId).c_str());
			
			auto sceneCameraPosition = (float*)m_CameraHandler.GetSceneCamera(i).Transform().Position;
			ImGui::DragFloat3((std::string("Position##") + cameraId).c_str(), sceneCameraPosition, 0.1f);

			auto sceneCameraRotation = (float*)m_CameraHandler.GetSceneCamera(i).Transform().Rotation;
			ImGui::DragFloat3((std::string("Rotation##") + cameraId).c_str(), sceneCameraRotation, 0.1f);

			ImGui::Separator();
		}
		
		ImGui::End();
	}

	void SandboxLayer::OnPollInput()
	{
	}

	void SandboxLayer::OnDetach()
	{
		for (auto i = 0; i < m_EntityList.size(); i++)
		{
			delete m_EntityList[i];
			m_EntityList[i] = nullptr;
		}

		m_EntityList.clear();

		m_CameraHandler.Terminate();
	}
}
