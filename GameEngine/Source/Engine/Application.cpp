#include "pch.h"
#include "Application.h"

namespace Engine
{
	Application::Application(ApplicationDescription description) :
		m_IsRunning{false},
		m_Description{std::move(description)},
		m_Windows{List<ScopePtr<Window>>()}
	{
	}

	Application::~Application() = default;

	auto Application::Initialize() -> bool
	{
		std::cout << "Initialize Application\n";
		for (const auto& window : m_Windows)
		{
			if (!window->Initialize(m_Description.ApplicationName,
			                        m_Description.StartWindowSize))
			{
				return false;
			}
		}

		std::cout << "Initialize Systems\n";
		InitializeSystems();

		for (const auto& window : m_Windows)
		{
			window->OnStart();
		}
		
		m_IsRunning = true;
		return true;
	}

	auto Application::Terminate() -> bool
	{
		std::cout << "Terminate Application\n";
		for (const auto& window : m_Windows)
		{
			if (!window->Terminate())
			{
				return false;
			}
		}

		std::cout << "Terminate Systems\n";
		TerminateSystems();
		m_IsRunning = false;
		return true;
	}

	auto Application::Run() -> void
	{
		// May be the blocking point when considering multiple windows
		const int numberOfWindows = static_cast<int>(m_Windows.size());
		int counter               = 0;
		while (m_IsRunning)
		{
			for (const auto& window : m_Windows)
			{
				if (window->IsRunning())
				{
					window->Broadcast();
				}
				else
				{
					counter++;
				}
			}

			if (counter >= numberOfWindows)
			{
				m_IsRunning = false;
			}
		}
	}
}
