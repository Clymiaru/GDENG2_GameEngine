#include "pch.h"
#include "Application.h"

#include "Time.h"
#include "Core/Layer.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/ShaderLibrary.h"

namespace Engine
{
	Application Application::m_Instance = Application();

	Application::Application() :
		m_IsRunning{false},
		m_Window{nullptr}
	{
	}

	Application::~Application() = default;

	void Application::Start(const Profile& profile)
	{
		m_Instance.m_Profile = CreateUniquePtr<Profile>(profile);
		
		m_Instance.m_Window = CreateUniquePtr<Window>(Window::Profile{
			m_Instance.m_Profile->Name,
			m_Instance.m_Profile->Width,
			m_Instance.m_Profile->Height
		});

		m_Instance.StartingSystems();

		m_Instance.m_IsRunning = true;
	}

	void Application::Run()
	{
		// Start all layers (Later will be deffered to Update as later created
		// layers will not start if utilizing this way)
		for (auto* layer : m_Instance.m_Layers)
		{
			layer->OnAttach();
		}

		while (m_Instance.m_IsRunning)
		{
			Time::LogFrameStart();

			m_Instance.PollEvents();
			m_Instance.Update();
			m_Instance.Render();

			Time::LogFrameEnd();

			Sleep(1);
		}

		for (auto* layer : m_Instance.m_Layers)
		{
			layer->OnDetach();
		}
	}

	void Application::Close()
	{
		m_Instance.ClosingSystems();
	}

	void Application::Quit()
	{
		m_Instance.m_IsRunning = false;
	}

	void Application::RegisterLayer(Layer* layer)
	{
		for (auto i = 0; i < m_Instance.m_Layers.size(); i++)
		{
			if (m_Instance.m_Layers[i]->GetName() == layer->GetName())
			{
				return;
			}
		}

		m_Instance.m_Layers.push_back(layer);
	}

	void Application::DeregisterLayer(Layer* layer)
	{
		for (auto i = 0; i < m_Instance.m_Layers.size(); i++)
		{
			if (m_Instance.m_Layers[i]->GetName() == layer->GetName())
			{
				layer->OnDetach();
				m_Instance.m_Layers.erase(m_Instance.m_Layers.begin() + i);
			}
		}
	}

	RECT Application::GetClientWindowRect()
	{
		return m_Instance.m_Window->GetClientWindowRect();
	}

	void Application::StartingSystems()
	{
		Time::Initialize();

		m_Window->Start();

		ShaderLibrary::GetInstance().Initialize();

		RenderSystem::Initialize(m_Window->GetHandle(),
		                         {1280, 720});
	}

	void Application::ClosingSystems()
	{
		Time::Terminate();
		ShaderLibrary::GetInstance().Terminate();
		RenderSystem::Terminate();
		m_Instance.m_Window->Close();
	}

	void Application::Update()
	{
		for (auto layer : m_Layers)
		{
			layer->OnUpdate();
		}
	}

	void Application::PollEvents()
	{
		m_Instance.m_Window->PollEvents();
	}

	void Application::Render()
	{
		for (auto layer : m_Layers)
		{
			layer->OnRender();
		}
	}
}
