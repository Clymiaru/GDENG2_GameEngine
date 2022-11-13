#include "pch.h"
#include "Window.h"

#include "Debug.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/UI/UISystem.h"

#include "Utils/Utils.h"

LRESULT CALLBACK WindowsProcedure(const HWND windowHandle,
                                  const UINT message,
                                  const WPARAM wParam,
                                  const LPARAM lParam)
{
	if (const LRESULT result = Engine::UISystem::HandleEvents(windowHandle,
	                                                          message,
	                                                          wParam,
	                                                          lParam);
		result)
	{
		return result;
	}

	switch (message)
	{
		case WM_CREATE:
		{
			auto* window = static_cast<Engine::Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
			SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			window->m_Handle = windowHandle;
			window->Open();
			break;
		}
		case WM_SIZE:
		{
			const UINT width  = LOWORD(lParam);
			const UINT height = HIWORD(lParam);

			auto* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));

			window->Resize(width, height);
			break;
		}
		case WM_SETFOCUS:
		{
			auto* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
			window->Focus();
			break;
		}
		case WM_KILLFOCUS:
		{
			auto* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
			window->Unfocus();
			break;
		}
		case WM_CLOSE:
		{
			auto* window = reinterpret_cast<Engine::Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
			window->Close();
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(windowHandle, message, wParam, lParam);
	}
	return 0;
}

namespace Engine
{
	Window::Window(const Specification& specs) :
		m_Specs{specs},
		m_Profile{},
		m_Handle{nullptr},
		m_Message{}
	{
		const std::wstring windowName = Utils::CStringToWString(specs.Name);

		WNDCLASSEX windowClass;
		windowClass.cbClsExtra    = NULL;
		windowClass.cbSize        = sizeof(WNDCLASSEX);
		windowClass.cbWndExtra    = NULL;
		windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		windowClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		windowClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hInstance     = nullptr;
		windowClass.lpszClassName = windowName.c_str();
		windowClass.lpszMenuName  = TEXT("");
		windowClass.style         = NULL;
		windowClass.lpfnWndProc   = &WindowsProcedure;

		const HRESULT registerResult = RegisterClassEx(&windowClass);
		Debug::Assert(registerResult, "Window cannot be registered!");

		const auto handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		                                   windowName.c_str(),
		                                   windowName.c_str(),
		                                   WS_OVERLAPPEDWINDOW,
		                                   CW_USEDEFAULT,
		                                   CW_USEDEFAULT,
		                                   (int)specs.Width,
		                                   (int)specs.Height,
		                                   nullptr,
		                                   nullptr,
		                                   nullptr,
		                                   this);

		Debug::Assert(handle, "Handle cannot be retrieved!");

		m_Profile.Name = specs.Name;
	}

	Window::~Window() { }

	void Window::PollEvents()
	{
		while (PeekMessage(&m_Message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}
	}
	void Window::ProcessEvents()
	{
		while (!m_EventQueue.empty())
		{
			auto* currentEvent = m_EventQueue.front();
			if (!m_EventListenerMap.contains(currentEvent->GetType()))
			{
				m_EventQueue.pop();
				delete currentEvent;
				continue;
			}

			for (auto f : m_EventListenerMap[currentEvent->GetType()])
			{
				if (!currentEvent->IsHandled)
				{
					currentEvent->IsHandled |= f(currentEvent);
				}
			}

			m_EventQueue.pop();
			delete currentEvent;
		}
	}
	void Window::SetEventCallback(const Event::Type eventType,
	                              std::function<bool(Event*)> callback)
	{
		if (!m_EventListenerMap.contains(eventType))
		{
			m_EventListenerMap[eventType] = List<std::function<bool(Event*)>>();
		}

		// TODO: Check for if this callback in stored already?
		m_EventListenerMap[eventType].push_back(callback);
	}

	HWND& Window::GetHandle()
	{
		return m_Handle;
	}

	const Window::Profile& Window::GetInfo() const
	{
		return m_Profile;
	}

	Window::Profile Window::GetInfo()
	{
		return m_Profile;
	}

	void Window::Open() const
	{
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
	}

	void Window::Close()
	{
		const auto result = DestroyWindow(m_Handle);
		Debug::Assert(result, "Window cannot be destroyed!");
		m_Profile.Width  = 0;
		m_Profile.Height = 0;
		m_Handle         = nullptr;

		m_EventQueue.push(new WindowCloseEvent());
	}

	void Window::Resize(const UINT width, const UINT height)
	{
		m_Profile.Width  = width;
		m_Profile.Height = height;
		// Renderer::Resize(Vector2Uint(width, height));

		m_EventQueue.push(new WindowResizeEvent(width, height));
	}

	void Window::Focus()
	{
		Debug::Log("Focus ON!");
		m_EventQueue.push(new WindowFocusEvent());
	}

	void Window::Unfocus()
	{
		Debug::Log("Focus OFF!");

		// Focus off should still progress simulations (ideally)
		// However, focus off should not respond to input commands.

		m_EventQueue.push(new WindowUnfocusEvent());
	}
}
