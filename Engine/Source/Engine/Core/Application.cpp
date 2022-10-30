#include "pch.h"
#include "Application.h"

#include "Window.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/ImGui/ImGuiSystem.h"
#include "Engine/Input/InputHandler.h"

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

	void Application::SetLayers(const List<Layer*> initialLayers)
	{
		for (size_t i = 0; i < initialLayers.size(); i++)
		{
			Instance().m_LayerSystem.Add(initialLayers[i]);
		}
	}

	void Application::Start(const Profile& profile)
	{
		ImGuiSystem::Instance().Start();

		Instance().m_Window = new Window(Window::Profile{
									   profile.Name,
									   profile.Width,
									   profile.Height
								   });

		Instance().StartSystems();
		Instance().m_IsRunning = true;
	}

	void Application::StartSystems()
	{
		Instance().m_Time = Time();

		m_Renderer = CreateSharedPtr<Renderer>(*m_Window);

		ShaderLibrary::Initialize(4, &*m_Renderer);

		m_InputHandler = new InputHandler();
		m_InputHandler->Start();

		Instance().m_LayerSystem.Start();
	}

	void Application::Run()
	{
		// Attach Loaded Layers

		while (Instance().m_IsRunning)
		{
			Instance().m_Time.Start();

			Instance().PollEvents();
			Instance().Update();
			Instance().Render();

			Instance().m_Time.End();

			Sleep(1);
		}

		// Detach Loaded Layers
	}

	void Application::End()
	{
		Instance().EndSystems();
	}

	void Application::EndSystems()
	{
		m_LayerSystem.End();

		ShaderLibrary::Terminate();

		// m_Renderer->End();
		m_Renderer.reset();

		delete m_Window;

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
		m_LayerSystem.Update();
	}

	void Application::PollEvents()
	{
		// Retrieve all input events that have been triggered this frame;
		// Pass the active input list to the layers.
		m_InputHandler->PollInputEvents();
		m_Window->PollEvents();

		m_LayerSystem.PollInput(m_InputHandler);
	}

	void Application::Render()
	{
		m_Renderer->Clear(Color{0.0f, 0.5f, 1.0f, 1.0f});

		m_LayerSystem.Render(&*m_Renderer);

		m_LayerSystem.ImGuiRender();

		m_Renderer->ShowFrame();
	}
}
