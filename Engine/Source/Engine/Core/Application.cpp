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

	std::string Application::AssetDataPath = "Assets/";

	Application::Application() :
		m_IsRunning{false},
		m_Window{nullptr},
		m_LayerHandler{nullptr}
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

		Renderer::Start(*m_Window);

		ImGuiSystem::Start(*m_Window,
		                   &Renderer::GetDevice(),
		                   &Renderer::GetDeviceContext().GetContext());

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

		ImGuiSystem::End();
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
		m_Window->PollEvents();
		Input::PollInputEvents();
		m_LayerHandler->PollInput();
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
