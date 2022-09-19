#include "Window.h"
#include "Utils/Pointers.h"
namespace Engine
{
	Window::Window(const std::wstring& windowName,
				   Vector2Int windowSize) :
		m_Handle(nullptr),
		m_IsRunning(false),
		m_WindowSize({ windowSize }),
		m_WindowName(windowName)
	{
	}

	Window::~Window()
	{
	}

	LRESULT CALLBACK WindowsProcedure(HWND windowHandle, 
									  UINT message, 
									  WPARAM wParam, 
									  LPARAM lParam)
	{
		switch (message)
		{
			case WM_CREATE:
			{
				auto* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
				SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)window);
				window->SetHandle(windowHandle);
				window->OnCreate();
				break;
			}
			case WM_DESTROY:
			{
				auto* window = (Window*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
				window->OnDestroy();
				PostQuitMessage(0);
				break;
			}
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
		}

		return NULL;
	}

	bool Window::Init()
	{
		WNDCLASSEX windowClass = {};
		windowClass.cbClsExtra = NULL;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.cbWndExtra = NULL;
		windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hInstance = NULL;
		windowClass.lpszClassName = m_WindowName.c_str();
		windowClass.lpszMenuName = TEXT("");
		windowClass.style = NULL;
		windowClass.lpfnWndProc = &WindowsProcedure;

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
								  NULL,
								  NULL,
								  NULL,
								  this);

		if (!m_Handle)
			return false;

		ShowWindow(m_Handle, SW_SHOW);
		UpdateWindow(m_Handle);

		m_IsRunning = true;

		return true;
	}

	bool Window::Release()
	{
		if (!DestroyWindow(m_Handle))
			return false;
		return true;
	}

	bool Window::Broadcast()
	{
		MSG message;

		OnUpdate();

		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		Sleep(1);
		return true;
	}

	bool Window::IsRunning()
	{
		return m_IsRunning;
	}

	void Window::OnCreate()
	{
	}

	void Window::OnUpdate()
	{
	}

	void Window::OnDestroy()
	{
		m_IsRunning = false;
	}

	RECT Window::GetClientWindowRect()
	{
		RECT rc;
		GetClientRect(m_Handle, &rc);
		return rc;
	}

	void Window::SetHandle(HWND windowHandle)
	{
		m_Handle = windowHandle;
	}
}
