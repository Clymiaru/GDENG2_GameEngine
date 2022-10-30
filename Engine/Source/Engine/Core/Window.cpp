#include "pch.h"
#include "Window.h"

#include "Debug.h"

#include "Application.h"

#include "../../../Dependencies/ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace Engine
{
	LRESULT CALLBACK WindowsProcedure(const HWND windowHandle,
									  const UINT message,
									  const WPARAM wParam,
									  const LPARAM lParam)
	{
		LRESULT result = ImGui_ImplWin32_WndProcHandler(windowHandle, message, wParam, lParam);
		if (result)
		{
			return result;
		}

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
	
	Window::Window(const Profile& profile) :
		m_Handle{nullptr},
		m_Message{}
	{
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

		const HRESULT registerResult = RegisterClassEx(&windowClass);
		Debug::Assert(registerResult, "Window cannot be registered!");

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
										   this);

		Debug::Assert(handle, "Handle cannot be retrieved!");

		UpdateClientSize();

		ShowWindow(m_Handle, SW_SHOW);

		ImGui_ImplWin32_Init(m_Handle);

		UpdateWindow(m_Handle);
	}

	Window::~Window()
	{
		const auto result = DestroyWindow(m_Handle);
		Debug::Assert(result, "Window cannot be destroyed!");
	}

	Rect<uint32_t>& Window::WindowRect()
	{
		return m_ClientRect;
	}

	void Window::UpdateClientSize()
	{
		RECT rect = {};
		GetClientRect(m_Handle, &rect);
		m_ClientRect = Rect<uint32_t>(0, 0, rect.right - rect.left, rect.bottom - rect.top);
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
}
