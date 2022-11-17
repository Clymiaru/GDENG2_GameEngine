#pragma once
#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Engine/Event/AEvent.h"

namespace Engine
{
	constexpr unsigned char KEY_STATE_FLAG  = 0x80;
	constexpr unsigned char KEY_TOGGLE_FLAG = 0x00;

	class Input final
	{
	public:
		Input();
		~Input();

		void PollInputEvents();

		static MouseInput Mouse();

		static KeyboardInput Keyboard();

		Input(const Input&)                = delete;
		Input& operator=(const Input&)     = delete;
		Input(Input&&) noexcept            = delete;
		Input& operator=(Input&&) noexcept = delete;

	private:
		static Input* s_Instance;

		unsigned char m_CurrentKeyState[256]{};
		unsigned char m_PrevKeyState[256]{};

		Vector2Int m_CurrentMousePosition;
		Vector2Int m_PrevMousePosition;

		KeyboardInput m_KeyInput;
		MouseInput m_MouseInput;
	};
}
