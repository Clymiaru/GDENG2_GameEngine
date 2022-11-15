#include "pch.h"
#include "Application.h"

#include "LayerHandler.h"
#include "Window.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Resource/ShaderLibrary.h"
#include "Engine/UI/UISystem.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const Specification& specs) :
		m_Specs{specs},
		m_Profile{},
		m_Window{nullptr},
		m_Timer{nullptr},
		m_LayerHandler{nullptr}
	{
		Debug::Assert(s_Instance == nullptr,
		              "There can only be 1 Application instantiated at any time!");
		s_Instance = this;
	}

	Application::~Application()
	{
		delete s_Instance; // Wouldn't this loop?
	}

	Application::Profile Application::GetInfo()
	{
		return s_Instance->m_Profile;
	}

	Window::Profile Application::GetWindowInfo()
	{
		return s_Instance->m_Window->GetInfo();
	}

	bool Application::Quit(Event* event)
	{
		s_Instance->m_Profile.IsRunning = false;
		return true;
	}

	void Application::Start()
	{
		const Window::Specification windowSpecs = Window::Specification{m_Specs.Name,
		                                                                m_Specs.InitialWindowWidth,
		                                                                m_Specs.InitialWindowHeight};
		s_Instance->m_Window = new Window(windowSpecs);

		s_Instance->m_Window->SetEventCallback(Event::Type::WindowClose,
		                                       [this](Event* event) -> bool
		                                       {
			                                       s_Instance->m_Profile.IsRunning = false;
			                                       return true;
		                                       });

		s_Instance->m_Window->SetEventCallback(Event::Type::WindowResize,
		                                       [this](Event* event) -> bool
		                                       {
			                                       const auto* e = (WindowResizeEvent*)event;
			                                       Renderer::Resize(Vector2Uint(e->Width, e->Height));
			                                       return true;
		                                       });

		s_Instance->m_Timer = new Timer();

		s_Instance->m_LayerHandler = new LayerHandler();

		// EventSystem::Init();

		Renderer::Start(*m_Window);

		UISystem::Start(*m_Window,
		                &Renderer::GetDevice(),
		                &Renderer::GetDeviceContext().GetContext());

		// ResourceLibrary::Init();
		ShaderLibrary::Initialize(4);

		Input::Start();

		for (size_t i = 0; i < m_Specs.InitialLayers.size(); i++)
		{
			s_Instance->m_LayerHandler->Add(m_Specs.InitialLayers[i]);
		}

		s_Instance->m_LayerHandler->StartLayers();

		s_Instance->m_Profile.IsRunning = true;
	}

	void Application::Run()
	{
		s_Instance->Start();

		while (s_Instance->m_Profile.IsRunning)
		{
			s_Instance->m_Timer->Start();

			s_Instance->PollEvents();
			s_Instance->Update();
			s_Instance->Render();

			s_Instance->m_Timer->Stop();

			Sleep(1);
		}

		s_Instance->End();
	}

	void Application::End()
	{
		s_Instance->m_LayerHandler->EndLayers();

		delete m_LayerHandler;

		ShaderLibrary::Terminate();

		UISystem::End();

		Renderer::End();

		Input::End();

		delete m_Window;
	}

	void Application::Update() const
	{
		s_Instance->m_Window->ProcessEvents();
		s_Instance->m_LayerHandler->Update();
	}

	void Application::PollEvents() const
	{
		s_Instance->m_Window->PollEvents();
		Input::PollInputEvents();
	}

	void Application::Render() const
	{
		Renderer::ClearFramebuffer(Renderer::GetSwapChain().GetBackbuffer());

		// Each layer has the responsibility to retarget the render target to
		// swap chain if framebuffer will not be utilized for now.
		m_LayerHandler->Render();

		Renderer::SetRenderTargetTo(&Renderer::GetSwapChain().GetBackbuffer().GetRenderTarget(),
		                            &Renderer::GetSwapChain().GetBackbuffer().GetDepthStencil());

		m_LayerHandler->ImGuiRender();

		Renderer::ShowFrame();
	}
}
