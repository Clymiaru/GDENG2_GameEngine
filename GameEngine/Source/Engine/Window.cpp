#include "pch.h"
#include "Window.h"

namespace Engine
{
	Window::Window() :
		m_Handle{nullptr},
		m_IsRunning{false},
		m_WindowSize{0, 0},
		m_WindowName{L"Untitled"}
	{
	}

	auto CALLBACK WindowsProcedure(const HWND windowHandle,
	                               const UINT message,
	                               const WPARAM wParam,
	                               const LPARAM lParam) -> LRESULT
	{
		switch (message)
		{
			case WM_CREATE:
			{
				auto* window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
				window->SetHandle(windowHandle);
				window->OnCreate();
				break;
			}
			case WM_DESTROY:
			{
				auto* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
				window->OnTerminate();
				PostQuitMessage(0);
				break;
			}
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
		}
		return 0;
	}

	auto Window::Initialize(const std::wstring windowName,
	                        const Vector2Int windowSize) -> bool
	{
		m_WindowSize = windowSize;
		m_WindowName = windowName;

		std::cout << "Initialize Window\n";

		WNDCLASSEX windowClass;
		windowClass.cbClsExtra    = NULL;
		windowClass.cbSize        = sizeof(WNDCLASSEX);
		windowClass.cbWndExtra    = NULL;
		windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		windowClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		windowClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
		windowClass.hInstance     = nullptr;
		windowClass.lpszClassName = m_WindowName.c_str();
		windowClass.lpszMenuName  = TEXT("");
		windowClass.style         = NULL;
		windowClass.lpfnWndProc   = &WindowsProcedure;

		if (!RegisterClassEx(&windowClass))
			return false;

		m_Handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		                          m_WindowName.c_str(),
		                          m_WindowName.c_str(),
		                          WS_OVERLAPPEDWINDOW,
		                          CW_USEDEFAULT,
		                          CW_USEDEFAULT,
		                          static_cast<int>(m_WindowSize.X),
		                          static_cast<int>(m_WindowSize.Y),
		                          nullptr,
		                          nullptr,
		                          nullptr,
		                          this);
		if (!m_Handle)
			return false;
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
		m_IsRunning = true;
		return true;
	}

	auto Window::Terminate() const -> bool
	{
		if (!DestroyWindow(m_Handle))
			return false;
		return true;
	}

	auto Window::Broadcast() -> bool
	{
		MSG message;
		OnUpdate();
		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		Sleep(1);
		return true;
	}

	auto Window::IsRunning() const -> bool
	{
		return m_IsRunning;
	}

	auto Window::OnCreate() -> void
	{
		std::cout << "Window Create\n";
	}

	auto Window::OnStart() -> void
	{
		std::cout << "Window Start\n";
	}

	auto Window::OnUpdate() -> void
	{
	}

	auto Window::OnTerminate() -> void
	{
		m_IsRunning = false;
		std::cout << "Window Terminate\n";
	}

	auto Window::GetClientWindowRect() const -> RECT
	{
		RECT rc;
		GetClientRect(m_Handle, &rc);
		return rc;
	}

	auto Window::GetHandle() const -> HWND
	{
		return m_Handle;
	}

	auto Window::SetHandle(const HWND windowHandle) -> void
	{
		m_Handle = windowHandle;
	}
}
