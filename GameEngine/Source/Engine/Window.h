#pragma once

#include <Windows.h>
#include "Utils/Math.h"
#include <string>

namespace Engine
{
	class Window
	{
	public:
		Window(const std::wstring& windowName, 
			   Vector2Int windowSize);
		virtual ~Window();

		bool Init();
		bool Release();
		bool Broadcast();
		bool IsRunning();

		virtual void OnCreate();
		virtual void OnUpdate();
		virtual void OnDestroy();

		RECT GetClientWindowRect();
		void SetHandle(HWND windowHandle);

	protected:
		HWND m_Handle;
		bool m_IsRunning;
		Vector2Int m_WindowSize;
		std::wstring m_WindowName;
	};
}