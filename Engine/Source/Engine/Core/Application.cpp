#include "pch.h"
#include "Application.h"
#include "Window.h"

#include "Engine/ECS/Core/EntityManager.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Input/Input.h"
#include "Engine/ResourceManagement/Core/ResourceSystem.h"
#include "Engine/UI/UISystem.h"

namespace Engine
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const Specification& specs) :
		m_Specs{specs},
		m_Profile{},
		m_Window{nullptr},
		m_SwapChain{nullptr},
		m_Timer{nullptr},
		m_Input{nullptr},
		m_ResourceSystem{nullptr},
		m_Renderer{nullptr},
		m_UISystem{nullptr},
		m_EntityManager{nullptr},
		m_LayerSystem{nullptr}
	{
		Debug::Assert(s_Instance == nullptr,
		              "There can only be 1 Application instantiated at any time!");
		s_Instance = this;
	}

	Application::~Application() = default;

	Application::Profile Application::GetInfo()
	{
		return s_Instance->m_Profile;
	}

	Window::Profile Application::GetWindowInfo()
	{
		return s_Instance->m_Window->GetInfo();
	}

	Renderer& Application::GetRenderer()
	{
		return *s_Instance->m_Renderer;
	}

	void Application::Start()
	{
		const Window::Specification windowSpecs = Window::Specification{m_Specs.Name,
		                                                                m_Specs.InitialWindowWidth,
		                                                                m_Specs.InitialWindowHeight};
		m_Window = new Window(windowSpecs);

		m_Window->SetEventCallback<WindowCloseEvent>([this](AEvent* event) -> bool
		{
			return OnWindowClose(event);
		});

		m_Window->SetEventCallback<WindowResizeEvent>([this](AEvent* event) -> bool
		{
			return OnWindowResize(event);
		});

		m_Window->SetEventCallback<WindowFocusEvent>([this](AEvent* event) -> bool
		{
			return OnWindowFocus(event);
		});

		m_Window->SetEventCallback<WindowUnfocusEvent>([this](AEvent* event) -> bool
		{
			return OnWindowUnfocus(event);
		});

		m_Timer = new Timer();

		m_Input = new Input();

		m_ResourceSystem = new ResourceSystem();

		m_Renderer = new Renderer();

		m_SwapChain = m_Renderer->GetDevice().CreateSwapChain(*m_Window);

		m_UISystem = new UISystem(*m_Window, *m_Renderer);

		m_EntityManager = new EntityManager();
		
		m_LayerSystem = new LayerSystem(m_Specs.InitialLayers.size());

		for (size_t i = 0; i < m_Specs.InitialLayers.size(); i++)
		{
			m_LayerSystem->Add(m_Specs.InitialLayers[i]);
		}

		

		m_LayerSystem->StartLayers();

		m_Profile.IsRunning = true;
	}

	void Application::Run()
	{
		Start();

		while (m_Profile.IsRunning)
		{
			m_Timer->Start();

			PollEvents();
			Update();
			Render();

			m_Timer->Stop();

			Sleep(1);
		}


		End();
	}

	void Application::End()
	{
		m_LayerSystem->EndLayers();
		delete m_LayerSystem;

		// delete m_EntityManager;

		//ShaderLibrary::Terminate();
		delete m_EntityManager;
		delete m_UISystem;

		delete m_SwapChain;
		delete m_Renderer;
		delete m_ResourceSystem;
		delete m_Input;
		delete m_Timer;

		delete m_Window;

		delete s_Instance;
	}

	void Application::Update() const
	{
		m_Window->ProcessEvents();
		// s_Instance->m_LayerHandler->Update();
	}

	void Application::PollEvents() const
	{
		m_Window->PollEvents();
		// Input::PollInputEvents();
	}

	void Application::Render() const
	{
		m_Renderer->StartRender(s_Instance->m_SwapChain->GetBackbuffer());

		m_LayerSystem->Render();

		m_SwapChain->Present(1);
	}

	bool Application::OnWindowClose(AEvent* e)
	{
		m_Profile.IsRunning = false;
		return true;
	}

	bool Application::OnWindowResize(AEvent* e) { return true; }

	bool Application::OnWindowFocus(AEvent* e) { return true; }

	bool Application::OnWindowUnfocus(AEvent* e) { return true; }
}
