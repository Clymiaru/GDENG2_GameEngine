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

		auto Initialize(const std::wstring& windowName,
		                const RectUint& windowRect) -> void;

		auto Terminate() const -> void;

		auto Broadcast() -> bool;

		[[nodiscard]]
		auto IsRunning() const -> bool;

		[[nodiscard]]
		auto GetClientWindowRect() const -> RECT;

		[[nodiscard]]
		auto GetHandle() const -> HWND;

		auto SetHandle(HWND windowHandle) -> void;

		auto Start() -> void;

		auto Update() -> void;

		auto Close() -> void;

	private:
		virtual auto OnStart() -> void = 0;

		virtual auto OnUpdate() -> void = 0;

		virtual auto OnRender() -> void = 0;

		virtual auto OnTerminate() -> void = 0;

	protected:
		HWND m_Handle;

		bool m_IsRunning;

		RectUint m_WindowRect;

		std::wstring m_WindowName;
	};
}
