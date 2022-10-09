#include "pch.h"
#include "Window.h"

#include "Application.h"

#include "Utils/Debug.h"

#include "Engine/Time.h"

namespace Engine
{
	Window::Window(Profile profile) :
		m_Handle{nullptr},
		m_IsRunning{false},
		m_Profile{std::move(profile)}
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

	auto Window::Start() -> void
	{
		Create(m_Profile);

		ShowWindow(m_Handle, SW_SHOW);

		UpdateWindow(m_Handle);

		m_IsRunning = true;
	}

	auto Window::Close() -> void
	{
		const auto result = DestroyWindow(m_Handle);
		ENGINE_ASSERT(result, "Window cannot be destroyed!")
	}

	auto Window::Run(List<Layer*> layers) -> void
	{
		MSG message;

		Time::LogFrameStart();

		PollEvents(&message);

		Update();

		for (auto* layer : layers)
		{
			layer->OnUpdate();
		}

		Render();

		for (auto* layer : layers)
		{
			layer->OnRender();
		}

		Time::LogFrameEnd();

		Sleep(1);
	}

	auto Window::PollEvents(MSG* message) -> void
	{
		while (PeekMessage(message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(message);
			DispatchMessage(message);
		}
	}

	auto Window::Update() -> void
	{
	}

	auto Window::Render() -> void
	{
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

	auto Window::SetHandle(HWND handle) -> void
	{
		m_Handle = handle;
	}

	auto Window::Create(const Profile profile) -> HWND
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

		ENGINE_ASSERT(RegisterClassEx(&windowClass), "Window cannot be registered!")

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

		ENGINE_ASSERT(handle, "Handle cannot be retrieved!")

		return handle;
	}
}
