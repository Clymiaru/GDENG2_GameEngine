#include "SandboxLayer.h"

#include <Utils/Random.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

#include "Engine/Graphics/RenderObjects/Cube.h"


Sandbox::SandboxLayer::SandboxLayer() :
	Layer{"SandboxLayer"},
	IInputListener{},
	m_CurrentTime{0.0f},
	m_MaxTime{5.0f}
{
}

Sandbox::SandboxLayer::~SandboxLayer() = default;

void Sandbox::SandboxLayer::OnAttach()
{
	using namespace Engine;
	ShaderLibrary::Register<VertexShader>(L"Assets/DefaultShader.hlsl",
	                                      "vsmain");

	ShaderLibrary::Register<PixelShader>(L"Assets/DefaultShader.hlsl",
	                                     "psmain");

	// Object initialization
	m_Plane = CreateUniquePtr<Plane>(Vector3(0,0,0), Vector3(500, 500.0f, 500), L"DefaultShader");

	m_TestCube = CreateUniquePtr<Cube>(Vector3(0,
	                                           0,
	                                           0),
	                                   Vector3(50,
	                                           50,
	                                           50),
	                                   L"DefaultShader");
	Debug::Log("Cubes: {0}", m_Cubes.size());

	InputSystem::Instance().AddListener(this);
}

void Sandbox::SandboxLayer::OnUpdate()
{
	m_CurrentTime = Engine::Application::DeltaTime();

	m_Plane->Update(m_CurrentTime);

	m_Plane->Position(Engine::Vector3{m_TestPosition[0], m_TestPosition[1], m_TestPosition[2]});
	m_Plane->Scale(Engine::Vector3{m_TestScale[0], m_TestScale[1], m_TestScale[2]});
	m_Plane->Rotation(Engine::Vector3{m_TestRotation[0], m_TestRotation[1], m_TestRotation[2]});

	m_TestCube->Position(Engine::Vector3{m_TestPosition2[0], m_TestPosition2[1], m_TestPosition2[2]});
	m_TestCube->Scale(Engine::Vector3{m_TestScale2[0], m_TestScale2[1], m_TestScale2[2]});
	m_TestCube->Rotation(Engine::Vector3{m_TestRotation2[0], m_TestRotation2[1], m_TestRotation2[2]});
	m_TestCube->Update(m_CurrentTime);

	Engine::InputSystem::Instance().Update();

}

void Sandbox::SandboxLayer::OnRender()
{
	m_TestCube->Draw();
	m_Plane->Draw();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Plane Controls");

	ImGui::DragFloat3("Position", m_TestPosition);
	ImGui::DragFloat3("Scale", m_TestScale);
	ImGui::DragFloat3("Rotation", m_TestRotation);
	
	ImGui::End();

	ImGui::Begin("Cube Controls");

	ImGui::DragFloat3("Position", m_TestPosition2);
	ImGui::DragFloat3("Scale", m_TestScale2);
	ImGui::DragFloat3("Rotation", m_TestRotation2);
	
	ImGui::End();

	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();
}

void Sandbox::SandboxLayer::OnDetach()
{
	Engine::InputSystem::Instance().RemoveListener(this);
	m_Tiles.clear();
}

void Sandbox::SandboxLayer::OnKeyDown(int keyCode)
{
	if (keyCode == 'W')
	{
		m_TestRotation[0] += Engine::Application::DeltaTime() * 3.14 * 0.1f;
	}
	else if (keyCode == 'S')
	{
		m_TestRotation[0] -= Engine::Application::DeltaTime() * 3.14 * 0.1f;
	}
	else if (keyCode == 'A')
	{
		m_TestRotation[1] += Engine::Application::DeltaTime() * 3.14 * 0.1f;
	}
	else if (keyCode == 'D')
	{
		m_TestRotation[1] -= Engine::Application::DeltaTime() * 3.14 * 0.1f;
	}
	Engine::Debug::Log("Moving!");
}

void Sandbox::SandboxLayer::OnKeyUp(int keyCode)
{
}
