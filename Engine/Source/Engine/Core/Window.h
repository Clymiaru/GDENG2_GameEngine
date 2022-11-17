#pragma once
#include <Windows.h>
#include <queue>

#include "Core.h"

#include "Engine/Event/AEvent.h"
#include <functional>

LRESULT CALLBACK WindowsProcedure(HWND windowHandle,
                                  UINT message,
                                  WPARAM wParam,
                                  LPARAM lParam);
namespace Engine
{
	class SwapChain;

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

		template <typename EventType>
		void SetEventCallback(std::function<bool(AEvent*)> callback);

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

		std::queue<AEvent*> m_EventQueue;

		HashMap<AEvent::Type, List<std::function<bool(AEvent*)>>> m_EventListenerMap;

		
		friend LRESULT CALLBACK ::WindowsProcedure(HWND windowHandle,
		                                           UINT message,
		                                           WPARAM wParam,
		                                           LPARAM lParam);
	};
	
	template <typename EventType>
	void Window::SetEventCallback(std::function<bool(AEvent*)> callback)
	{
		if (!m_EventListenerMap.contains(EventType::GetStaticType()))
		{
			m_EventListenerMap[EventType::GetStaticType()] = List<std::function<bool(AEvent*)>>();
		}

		// TODO: Check for if this callback in stored already?
		m_EventListenerMap[EventType::GetStaticType()].push_back(callback);
	}
}
