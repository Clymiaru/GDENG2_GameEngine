#include "pch.h"
#include "Window.h"

#include "Utils/Debug.h"

namespace Engine
{
	Window::Window() :
		m_Handle{nullptr},
		m_IsRunning{false},
		m_WindowRect{0, 0, 0, 0},
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
				break;
			}
			case WM_DESTROY:
			{
				auto* window = reinterpret_cast<Window*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
				window->Close();
				PostQuitMessage(0);
				break;
			}
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
		}
		return 0;
	}

	auto Window::Initialize(const std::wstring& windowName,
	                        const RectUint& windowRect) -> void
	{
		m_WindowRect = windowRect;
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

		ENGINE_ASSERT(RegisterClassEx(&windowClass), "Window cannot be registered!")

		m_Handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		                          m_WindowName.c_str(),
		                          m_WindowName.c_str(),
		                          WS_OVERLAPPEDWINDOW,
		                          CW_USEDEFAULT,
		                          CW_USEDEFAULT,
		                          static_cast<int>(m_WindowRect.Width),
		                          static_cast<int>(m_WindowRect.Height),
		                          nullptr,
		                          nullptr,
		                          nullptr,
		                          this);

		ENGINE_ASSERT(m_Handle, "Handle cannot be retrieved!")
		
		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);
		m_IsRunning = true;
	}

	auto Window::Terminate() const -> void
	{
		const auto result = DestroyWindow(m_Handle);
		ENGINE_ASSERT(!result, "Window cannot be destroyed!")
	}

	auto Window::Broadcast() -> bool
	{
		MSG message;
		Update();
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

	auto Window::Start() -> void
	{
		OnStart();
	}

	auto Window::Update() -> void
	{
		OnUpdate();
		OnRender();
	}

	auto Window::Close() -> void
	{
		m_IsRunning = false;
		OnTerminate();
	}
}
