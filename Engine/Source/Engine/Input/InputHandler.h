#pragma once
#include "Engine/Core/Core.h"
#include "Engine/Event/Event.h"

namespace Engine
{
	constexpr unsigned char KEY_STATE_FLAG =  0x80;
	constexpr unsigned char KEY_TOGGLE_FLAG = 0x00;
	
	class InputHandler final
	{
	public:
		InputHandler() = default;
		~InputHandler() = default;

		void Start();

		void End();
		
		void PollInputEvents();

		KeyEvent& ActiveKeyInput();
		MouseEvent& ActiveMouseInput();

	private:
		HashMap<Event::Type, Event*> m_EventMap{};

		unsigned char m_CurrentKeyState[256] = {};
		unsigned char m_PrevKeyState[256] = {};

		Vector2Int m_CurrentMousePosition;
		Vector2Int m_PrevMousePosition;
	};
}
