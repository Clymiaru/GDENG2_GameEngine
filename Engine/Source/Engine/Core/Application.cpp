#include "pch.h"
#include "Application.h"

#include "Window.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

#include "Engine/ImGui/ImGuiSystem.h"
#include "Engine/Input/InputSystem.h"

namespace Engine
{
	Application Application::m_Instance;

	Application::Application() :
		m_IsRunning{false},
		m_Window{nullptr},
		m_LayerSystem{5}
	{
	}

	Application::~Application() = default;

	Application& Application::Instance()
	{
		return m_Instance;
	}

	void Application::SetProfile(const Profile& profile)
	{
		Instance().m_Profile = profile;
	}

	void Application::SetInitialLayers(const List<Layer*> initialLayers)
	{
		for (size_t i = 0; i < initialLayers.size(); i++)
		{
			Instance().m_LayerSystem.Add(initialLayers[i]);
		}
	}

	void Application::Start()
	{
		ImGuiSystem::Instance().Start();
		
		Instance().m_Window = Window::Create(Window::Profile{
			Instance().m_Profile.Name,
			Instance().m_Profile.Width,
			Instance().m_Profile.Height
		});

		Instance().StartSystems();
		Instance().m_IsRunning = true;
	}

	void Application::StartSystems()
	{
		Instance().m_Time = Time();
		Instance().m_Window->Start();
		RenderSystem::Start(*m_Window);

		

		ShaderLibrary::Initialize(4);

		Instance().m_LayerSystem.Start();
	}

	void Application::Run()
	{
		while (Instance().m_IsRunning)
		{
			Instance().m_Time.Start();

			Instance().PollEvents();
			Instance().Update();
			Instance().Render();

			Instance().m_Time.End();

			Sleep(1);
		}
	}

	void Application::End()
	{
		Instance().EndSystems();
	}

	void Application::EndSystems()
	{
		ShaderLibrary::Terminate();
		Instance().m_LayerSystem.End();

		RenderSystem::End();

		Instance().m_Window->Close();

		ImGuiSystem::Instance().End();
	}

	void Application::Quit()
	{
		Instance().m_IsRunning = false;
	}

	double Application::DeltaTime()
	{
		return Instance().m_Time.DeltaTime();
	}

	Window& Application::WindowRef()
	{
		return *Instance().m_Window;
	}

	void Application::Update()
	{
		// for (auto layer : m_Layers)
		// {
		// 	layer->OnUpdate();
		// }
		m_LayerSystem.Update();
	}

	void Application::PollEvents()
	{
		Instance().m_Window->PollEvents();
	}

	void Application::Render()
	{
		RenderSystem::Clear({0.0f, 0.5f, 1.0f, 1.0f});

		m_LayerSystem.Render();

		RenderSystem::ShowFrame();
	}
}