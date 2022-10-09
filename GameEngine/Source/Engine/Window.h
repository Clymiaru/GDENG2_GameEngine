#pragma once
#include <Windows.h>
#include <string>

#include "Core/Layer.h"

#include "Utils/DataStructures.h"
#include "Utils/Math.h"

namespace Engine
{
	class Application;
	class Window
	{
	public:
		struct Profile
		{
			std::wstring Name;
			Uint Width;
			Uint Height;
		};
		
		Window(Profile profile);

		virtual ~Window() = default;

		auto Run(List<Layer*> layers) -> void;

		[[nodiscard]]
		auto GetClientWindowRect() const -> RECT;

		[[nodiscard]]
		auto GetHandle() const -> HWND;

		auto SetHandle(HWND handle) -> void;

	private:
		auto Start() -> void;

		static auto PollEvents(MSG* message) -> void;

		auto Update() -> void;

		auto Render() -> void;
		
		auto Close() -> void;
		
		auto Create(Profile profile) -> HWND;

		HWND m_Handle;

		bool m_IsRunning;

		Profile m_Profile;

		List<Layer*> m_Layers;

		friend class Application;
	};
}
