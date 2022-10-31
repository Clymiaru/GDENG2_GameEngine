#include "SandboxLayer.h"

#include <Engine/ECS/Component/RenderComponent.h>
#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/Input/Input.h>

#include "Engine/ECS/Entity/Entity.h"
#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Rendering System
// TODO: Camera
// TODO: Goal: Render 3 Cubes with Camera Movement

namespace Sandbox
{
	SandboxLayer::SandboxLayer() :
		Layer{L"SandboxLayer"},
		m_EntityList{Engine::List<Engine::Entity*>()}
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

		Entity* cubeEntity = new Entity(L"Testing Entity");
		cubeEntity->Transform().Scale(Vector3Float(100.0f, 100.0f, 100.0f));
		m_EntityList.emplace_back(cubeEntity);

		//
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
	}

	void SandboxLayer::OnRender()
	{
		// FOR TEST RENDERING SYSTEM

		for (auto* entity : m_EntityList)
		{
			entity->Render().Draw();
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

			auto entityPosition = (float*)entity->Transform().Position();

			ImGui::DragFloat3("Position", entityPosition);

			entity->Transform().Position(Engine::Vector3Float(entityPosition[0], entityPosition[1], entityPosition[2]));

			auto entityScale = (float*)entity->Transform().Scale();
			ImGui::DragFloat3("Scale", entityScale);

			entity->Transform().Scale(Engine::Vector3Float(entityScale[0], entityScale[1], entityScale[2]));
		}

		ImGui::Text("Delta Time: %f", Engine::Application::DeltaTime());
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
	}
}
