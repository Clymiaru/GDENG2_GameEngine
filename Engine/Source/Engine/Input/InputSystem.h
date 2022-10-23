#pragma once
#include <unordered_set>

#include "IInputListener.h"

namespace Engine
{
	const unsigned char KEY_UP_CODE =  0x80;
	
	class InputSystem final
	{
	public:
		static InputSystem& Instance();

		void PollInputEvents();

		void Update();
		void AddListener(IInputListener* inputListener);
		void RemoveListener(IInputListener* inputListener);

	private:
		InputSystem() = default;
		~InputSystem() = default;

		std::unordered_set<IInputListener*> m_Listeners;

		unsigned char m_KeyState[256] = {};
		unsigned char m_PrevKeyState[256] = {};

		Vector2 m_PrevMousePosition;
		bool m_IsFirstTime = true;
	};
}
