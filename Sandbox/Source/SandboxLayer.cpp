#include "SandboxLayer.h"

#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/Input/InputHandler.h>

#include "Engine/ECS/Entity/Entity.h"
#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Rendering System
// TODO: Camera
// TODO: Goal: Render 3 Cubes with Camera Movement

namespace Sandbox
{
	SandboxLayer::SandboxLayer() :
		Layer{L"SandboxLayer"},
		m_EntityList{Engine::List<Engine::Entity*>()},
		m_ActiveMouseEvent{new Engine::MouseEvent()},
		m_ActiveKeyEvent(new Engine::KeyEvent())
	{
	}

	SandboxLayer::~SandboxLayer() = default;

	void SandboxLayer::OnAttach()
	{
		Engine::Entity* cubeEntity = new Engine::Entity(L"Testing Entity");
		m_EntityList.emplace_back(cubeEntity);

		Engine::Entity* cubeEntity2 = new Engine::Entity(L"Testing Entity 2");
		m_EntityList.emplace_back(cubeEntity2);

		// using namespace Engine;
		// ShaderLibrary::Register<VertexShader>(L"Assets/DefaultShader.hlsl",
		//                                       "vsmain");
		//
		// ShaderLibrary::Register<PixelShader>(L"Assets/DefaultShader.hlsl",
		//                                      "psmain");
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
			ImGui::DragFloat3("Position", (float*)entity->Transform().Position());
		}

		ImGui::Text("Delta Time: %f", Engine::Application::DeltaTime());
		ImGui::Text("Key Event Status");
		ImGui::Text("Key Pressed: %c", (char)m_ActiveKeyEvent->KeyCode);
		ImGui::Text("Key State: %s", KeyStateToString(m_ActiveKeyEvent->KeyState).c_str());
		ImGui::Spacing();
		ImGui::Text("Mouse Event Status");
		ImGui::Text("Mouse Position: %i, %i", m_ActiveMouseEvent->MousePosition.x, m_ActiveMouseEvent->MousePosition.y);
		ImGui::Text("Mouse Button: %s", MouseButtonToString(m_ActiveMouseEvent->Button).c_str());
		ImGui::Text("Mouse State: %s", MouseStateToString(m_ActiveMouseEvent->State).c_str());
		ImGui::Text("Delta Mouse Position: %i, %i", m_ActiveMouseEvent->DeltaMousePosition.x,
		            m_ActiveMouseEvent->DeltaMousePosition.y);
		ImGui::End();
	}

	void SandboxLayer::OnPollInput(Engine::InputHandler* inputHandlerRef)
	{
		m_ActiveKeyEvent   = &inputHandlerRef->ActiveKeyInput();
		m_ActiveMouseEvent = &inputHandlerRef->ActiveMouseInput();
	}

	void SandboxLayer::OnDetach()
	{
		for (auto i = 0; i < m_EntityList.size(); i++)
		{
			delete m_EntityList[i];
			m_EntityList[i] = nullptr;
		}

		m_EntityList.clear();

		delete m_ActiveMouseEvent;
		delete m_ActiveKeyEvent;
	}
}
