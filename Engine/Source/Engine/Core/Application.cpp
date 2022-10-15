﻿#include "pch.h"
#include "Application.h"

#include <Engine/Time.h>

namespace Engine
{
	Application::Application() :
		m_IsRunning{false},
		m_Window{nullptr}
	{
	}

	Application::~Application() = default;

	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	void Application::SetProfile(const Profile& profile)
	{
		Instance().m_Profile = profile;
	}

	void Application::Start()
	{
		Instance().m_Window = Window::Create(Window::Profile{
			Instance().m_Profile.Name,
			Instance().m_Profile.Width,
			Instance().m_Profile.Height
		});

		Instance().StartingSystems();
		Instance().m_IsRunning = true;
	}

	void Application::StartingSystems()
	{
		// Time::Initialize();
		
		Instance().m_Window->Start();
		
		// ShaderLibrary::Initialize(4);
		//
		// RenderSystem::Initialize(m_Window->GetHandle(),
		//                          {1280, 720});
	}

	void Application::Run()
	{
		while (Instance().m_IsRunning)
		{
			// Time::LogFrameStart();

			Instance().PollEvents();
			Instance().Update();
			Instance().Render();

			// Time::LogFrameEnd();

			Sleep(1);
		}
	}

	void Application::End()
	{
		Instance().EndingSystems();
	}

	void Application::EndingSystems()
	{
		// Time::Terminate();
		// ShaderLibrary::Terminate();
		// RenderSystem::Terminate();
		Instance().m_Window->Close();
	}

	void Application::Quit()
	{
		Instance().m_IsRunning = false;
	}

	void Application::Update()
	{
		// for (auto layer : m_Layers)
		// {
		// 	layer->OnUpdate();
		// }
	}

	void Application::PollEvents()
	{
		Instance().m_Window->PollEvents();
	}

	void Application::Render()
	{
		// for (auto layer : m_Layers)
		// {
		// 	layer->OnRender();
		// }
	}
}
