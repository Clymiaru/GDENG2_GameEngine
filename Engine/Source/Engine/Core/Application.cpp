#include "pch.h"
#include "Application.h"

#include "LayerHandler.h"
#include "Window.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/ImGui/ImGuiSystem.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	Application Application::m_Instance;

	Application::Application() :
		m_IsRunning{false},
		m_Window{nullptr}
	{
		m_LayerHandler = CreateUniquePtr<LayerHandler>(5);
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
			Instance().m_LayerHandler->Add(initialLayers[i]);
		}
	}

	void Application::Start(const Profile& profile)
	{
		ImGuiSystem::Instance().Start();

		Instance().m_Window = CreateUniquePtr<Window>(Window::Profile{
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

		Renderer::Start(*m_Window);;

		ShaderLibrary::Initialize(4);

		Input::Start();
	}

	void Application::Run()
	{
		Instance().m_LayerHandler->StartLayers();

		while (Instance().m_IsRunning)
		{
			Instance().m_Time.Start();

			Instance().PollEvents();
			Instance().Update();
			Instance().Render();

			Instance().m_Time.End();

			Sleep(1);
		}

		Instance().m_LayerHandler->EndLayers();
	}

	void Application::End()
	{
		Instance().EndSystems();
	}

	void Application::EndSystems()
	{
		m_LayerHandler.reset();

		ShaderLibrary::Terminate();

		Renderer::End();

		Input::End();

		m_Window.reset();

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

	Rect<uint32_t> Application::WindowRect()
	{
		return Instance().m_Window->WindowRect();
	}

	void Application::Update() const
	{
		m_LayerHandler->Update();
	}

	void Application::PollEvents() const
	{
		Input::PollInputEvents();
		m_Window->PollEvents();
		m_LayerHandler->PollInput();
	}

	void Application::Render() const
	{
		Renderer::Clear(Color{0.0f, 0.5f, 1.0f, 1.0f});

		m_LayerHandler->Render();

		ImGuiIO& io = ImGui::GetIO();

		const Rect<uint32_t> windowRect = WindowRect();

		io.DisplaySize = ImVec2(windowRect.Width, windowRect.Height);

		m_LayerHandler->ImGuiRender();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		Renderer::ShowFrame();
	}
}
