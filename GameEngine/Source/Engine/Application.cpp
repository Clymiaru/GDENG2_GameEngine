#include "pch.h"
#include "Application.h"

#include "Time.h"

namespace Engine
{
	Application::Application(ApplicationDescription description) :
		m_IsRunning{false},
		m_Description{std::move(description)},
		m_Window{UniquePtr<Window>()}
	{
	}

	Application::~Application() = default;

	auto Application::Initialize() -> void
	{
		std::cout << "Initialize Application\n";

		const auto windowSize = Vector2Uint{
			m_Description.StartWindowRect.Right - m_Description.StartWindowRect.Left,
			m_Description.StartWindowRect.Bottom - m_Description.StartWindowRect.Top
		};

		Time::Initialize();

		m_Window->Initialize(m_Description.ApplicationName,
		                     m_Description.StartWindowRect);

		std::cout << "Initialize Systems\n";
		InitializeSystems();

		m_Window->Start();

		m_IsRunning = true;
	}

	auto Application::Terminate() -> void
	{
		std::cout << "Terminate Application\n";

		m_Window->Terminate();
		Time::Terminate();

		std::cout << "Terminate Systems\n";
		TerminateSystems();
		m_IsRunning = false;
	}

	auto Application::Run() -> void
	{
		// May be the blocking point when considering multiple windows
		while (m_Window->IsRunning())
		{
			m_Window->Broadcast();
		}

		m_IsRunning = false;
	}
}
