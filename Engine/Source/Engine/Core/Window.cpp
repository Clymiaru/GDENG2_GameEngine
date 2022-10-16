#include "pch.h"
#include "Window.h"

#include "Debug.h"

#include "Application.h"

namespace Engine
{
	Window::Window() :
		m_Handle{nullptr},
		m_Message{}
	{
	}

	Window::~Window() = default;

	LRESULT CALLBACK WindowsProcedure(const HWND windowHandle,
	                                  const UINT message,
	                                  const WPARAM wParam,
	                                  const LPARAM lParam)
	{
		switch (message)
		{
			case WM_CREATE:
			{
				auto* window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
				window->m_Handle = windowHandle;
				window->UpdateClientSize();
				break;
			}
			case WM_CLOSE:
			{
				Application::Quit();
				break;
			}
			case WM_DESTROY:
			{
				break;
			}
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
		}
		return 0;
	}

	void Window::Start()
	{
		UpdateClientSize();

		ShowWindow(m_Handle, SW_SHOW);

		UpdateWindow(m_Handle);
	}

	void Window::Close()
	{
		const auto result = DestroyWindow(m_Handle);
		ENGINE_ASSERT(result, "Window cannot be destroyed!")
		delete this;
	}

	Vector2 Window::GetSize()
	{
		return m_ClientSize;
	}

	void Window::UpdateClientSize()
	{
		RECT rect = {};
		GetClientRect(m_Handle, &rect);
		m_ClientSize.X(static_cast<float>(rect.right - rect.left));
		m_ClientSize.Y(static_cast<float>(rect.bottom - rect.top));
	}

	HWND& Window::GetHandle()
	{
		return m_Handle;
	}

	void Window::PollEvents()
	{
		while (PeekMessage(&m_Message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}
	}

	Window* Window::Create(const Profile& profile)
	{
		Window* window = new Window();

		WNDCLASSEX windowClass;
		windowClass.cbClsExtra    = NULL;
		windowClass.cbSize        = sizeof(WNDCLASSEX);
		windowClass.cbWndExtra    = NULL;
		windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		windowClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		windowClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hInstance     = nullptr;
		windowClass.lpszClassName = profile.Name.c_str();
		windowClass.lpszMenuName  = TEXT("");
		windowClass.style         = NULL;
		windowClass.lpfnWndProc   = &WindowsProcedure;

		HRESULT registerResult = RegisterClassEx(&windowClass);
		ENGINE_ASSERT(registerResult, "Window cannot be registered!")

		const auto handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		                                   profile.Name.c_str(),
		                                   profile.Name.c_str(),
		                                   WS_OVERLAPPEDWINDOW,
		                                   CW_USEDEFAULT,
		                                   CW_USEDEFAULT,
		                                   static_cast<int>(profile.Width),
		                                   static_cast<int>(profile.Height),
		                                   nullptr,
		                                   nullptr,
		                                   nullptr,
		                                   window);

		ENGINE_ASSERT(handle, "Handle cannot be retrieved!")

		return window;
	}
}
