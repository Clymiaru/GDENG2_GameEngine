#pragma once
#include <Windows.h>
#include <string>
#include "Utils/Math.h"

namespace Engine
{
	class Window
	{
	public:
		Window(std::wstring windowName,
		       Vector2Int windowSize);

		virtual ~Window() = default;

		auto Init() -> bool;

		[[nodiscard]]
		auto Release() const -> bool;

		auto Broadcast() -> bool;

		[[nodiscard]]
		auto IsRunning() const -> bool;

		[[nodiscard]]
		auto GetClientWindowRect() const -> RECT;

		auto SetHandle(HWND windowHandle) -> void;

		virtual auto OnCreate() -> void;

		virtual auto OnUpdate() -> void;

		virtual auto OnDestroy() -> void;

	protected:
		HWND m_Handle;

		bool m_IsRunning;

		Vector2Int m_WindowSize;

		std::wstring m_WindowName;
	};
}
