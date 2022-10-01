#pragma once
#include <Windows.h>
#include <string>
#include "Utils/Math.h"

namespace Engine
{
	class Window
	{
	public:
		Window();

		virtual ~Window() = default;

		auto Initialize(std::wstring windowName,
		                Vector2Int windowSize) -> bool;

		[[nodiscard]]
		auto Terminate() const -> bool;

		auto Broadcast() -> bool;

		[[nodiscard]]
		auto IsRunning() const -> bool;

		[[nodiscard]]
		auto GetClientWindowRect() const -> RECT;

		[[nodiscard]]
		auto GetHandle() const -> HWND;

		auto SetHandle(HWND windowHandle) -> void;

		virtual auto OnCreate() -> void;	

		virtual auto OnStart() -> void;

		virtual auto OnUpdate() -> void;

		virtual auto OnTerminate() -> void;

	protected:
		HWND m_Handle;

		bool m_IsRunning;

		Vector2Int m_WindowSize;

		std::wstring m_WindowName;
	};
}
