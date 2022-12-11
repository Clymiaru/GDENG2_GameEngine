#pragma once
#include "InputData.h"

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

		InputData GetInput() const;

		Input(const Input&)                = delete;
		Input& operator=(const Input&)     = delete;
		Input(Input&&) noexcept            = delete;
		Input& operator=(Input&&) noexcept = delete;

	private:
		unsigned char m_CurrentKeyState[256]{};
		unsigned char m_PrevKeyState[256]{};

		Vector2Int m_CurrentMousePosition;
		Vector2Int m_PrevMousePosition;

		KeyboardInput m_KeyInput;
		MouseInput m_MouseInput;
	};
}
