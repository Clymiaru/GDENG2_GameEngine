#include "pch.h"
#include "Window.h"
#include "Utils/Pointers.h"

namespace Engine
{
	Window::Window(std::wstring windowName,
	               Vector2Int windowSize) :
		m_Handle{nullptr},
		m_IsRunning{false},
		m_WindowSize{windowSize},
		m_WindowName{std::move(windowName)}
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
				auto window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
				window->SetHandle(windowHandle);
				window->OnCreate();
				break;
			}
			case WM_DESTROY:
			{
				auto* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
				window->OnDestroy();
				PostQuitMessage(0);
				break;
			}
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
		}
		return 0;
	}

	auto Window::Init() -> bool
	{
		WNDCLASSEX windowClass    = {};
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
		                          m_WindowSize.X,
		                          m_WindowSize.Y,
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

	auto Window::Release() const -> bool
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
	}

	auto Window::OnUpdate() -> void
	{
	}

	auto Window::OnDestroy() -> void
	{
		m_IsRunning = false;
	}

	auto Window::GetClientWindowRect() const -> RECT
	{
		RECT rc;
		GetClientRect(m_Handle, &rc);
		return rc;
	}

	auto Window::SetHandle(const HWND windowHandle) -> void
	{
		m_Handle = windowHandle;
	}
}
