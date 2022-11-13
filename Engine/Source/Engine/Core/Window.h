#pragma once
#include <Windows.h>
#include <queue>

#include "Core.h"

#include "Engine/Event/Event.h"

LRESULT CALLBACK WindowsProcedure(HWND windowHandle,
                                  UINT message,
                                  WPARAM wParam,
                                  LPARAM lParam);
namespace Engine
{
	class Window final
	{
	public:
		struct Specification
		{
			String Name         = "Unnamed";
			unsigned int Width  = 640;
			unsigned int Height = 480;
		};

		struct Profile
		{
			String Name         = "Unnamed";
			unsigned int Width  = 0;
			unsigned int Height = 0;
		};

		explicit Window(const Specification& specs);

		~Window();

		void PollEvents();

		void ProcessEvents();

		void SetEventCallback(Event::Type eventType,
		                      std::function<bool(Event*)> callback);

		[[nodiscard]]
		HWND& GetHandle();

		[[nodiscard]]
		const Profile& GetInfo() const;

		[[nodiscard]]
		Profile GetInfo();

		Window(const Window&)                = delete;
		Window& operator=(const Window&)     = delete;
		Window(Window&&) noexcept            = delete;
		Window& operator=(Window&&) noexcept = delete;

	private:
		void Open() const;

		void Close();

		void Resize(UINT width, UINT height);

		void Focus();

		void Unfocus();

		Specification m_Specs;

		Profile m_Profile;

		HWND m_Handle;

		MSG m_Message;

		std::queue<Event*> m_EventQueue;

		HashMap<Event::Type, List<std::function<bool(Event*)>>> m_EventListenerMap;

		friend LRESULT CALLBACK ::WindowsProcedure(HWND windowHandle,
		                                           UINT message,
		                                           WPARAM wParam,
		                                           LPARAM lParam);
	};
}
