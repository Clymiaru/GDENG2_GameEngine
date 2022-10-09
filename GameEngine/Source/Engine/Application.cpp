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

	auto Application::Start(Window::Profile windowProfile) -> void
	{
		m_Window = CreateUniquePtr<Window>(windowProfile);

		StartingSystems();

		m_IsRunning = true;
	}

	auto Application::Close() -> void
	{
		// Layer* layer = nullptr;
		// for (auto i = 0; i < m_Instance.m_Layers.size(); i++)
		// {
		// 	m_Instance.m_Layers[i]->OnDetach();
		// 	layer = m_Instance.m_Layers[i];
		// 	m_Instance.m_Layers[i] = nullptr;
		// 	delete layer;
		// }

		Time::Terminate();
		ShaderLibrary::GetInstance().Terminate();
		RenderSystem::Terminate();
		m_Instance.m_Window->Close();
	}

	Application::~Application() = default;

	auto Application::Run(Window::Profile windowProfile) -> void
	{
		m_Instance.Start(windowProfile);

		// Start all layers (Later will be deffered to Update as later created
		// layers will not start if utilizing this way)
		for (auto* layer : m_Instance.m_Layers)
		{
			layer->OnAttach();
		}

		while (m_Instance.m_IsRunning)
		{
			m_Instance.m_Window->Run(m_Instance.m_Layers);
		}

		for (auto* layer : m_Instance.m_Layers)
		{
			layer->OnDetach();
		}

		m_Instance.Close();
	}

	auto Application::Quit() -> void
	{
		m_Instance.m_IsRunning = false;
	}

	auto Application::RegisterLayer(Layer* layer) -> void
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

	auto Application::DeregisterLayer(Layer* layer) -> void
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

	auto Application::GetClientWindowRect() -> RECT
	{
		return m_Instance.m_Window->GetClientWindowRect();
	}

	auto Application::StartingSystems() -> void
	{
		Time::Initialize();

		m_Window->Start();

		ShaderLibrary::GetInstance().Initialize();

		RenderSystem::Initialize(m_Window->GetHandle(),
		                         {1280, 720});
	}

	auto Application::ClosingSystems() -> void
	{
	}

	auto Application::Update() -> void
	{
		for (auto layer : m_Layers)
		{
			layer->OnUpdate();
		}
	}

	auto Application::PollEvents() -> void
	{
	}

	auto Application::Render() -> void
	{
		for (auto layer : m_Layers)
		{
			layer->OnRender();
		}
	}
}
