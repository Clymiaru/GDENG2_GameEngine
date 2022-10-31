#pragma once
#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Engine/Event/Event.h"

namespace Engine
{
	constexpr unsigned char KEY_STATE_FLAG =  0x80;
	constexpr unsigned char KEY_TOGGLE_FLAG = 0x00;
	
	class Input final
	{
	public:
		static void Start();

		static void End();
		
		static void PollInputEvents();

		static MouseInput Mouse();

		static KeyboardInput Keyboard();

	private:
		static void UpdateMouseInput();
		
		static unsigned char s_CurrentKeyState[256];
		static unsigned char s_PrevKeyState[256];

		static Vector2Int s_CurrentMousePosition;
		static Vector2Int s_PrevMousePosition;

		static KeyboardInput s_KeyInput;
		static MouseInput s_MouseInput;
	};
}
