#include "pch.h"
#include "Input.h"

#include <Windows.h>

#include "Engine/Core/Debug.h"
#include "Engine/Math/Vector2.h"

namespace Engine
{
	struct KeyEvent;

	unsigned char Input::s_CurrentKeyState[256] = {};

	unsigned char Input::s_PrevKeyState[256] = {};

	Vector2Int Input::s_CurrentMousePosition = Vector2Int();

	Vector2Int Input::s_PrevMousePosition = Vector2Int();

	KeyboardInput Input::s_KeyInput = {KeyCode::None, KeyState::None, 0};

	MouseInput Input::s_MouseInput = {Vector2Int(), Vector2Int(), MouseButton::None, MouseState::None};

	void Input::Start()
	{
		s_PrevMousePosition    = Vector2Int();
		s_CurrentMousePosition = Vector2Int();
	}

	void Input::End()
	{
	}

	KeyCode TranslateVirtualKeyCodeToKeyCode(unsigned char vkCode)
	{
		if (vkCode >= 'A' && vkCode <= 'Z' ||
		    vkCode >= '0' && vkCode <= '9')
		{
			return (KeyCode)vkCode;
		}
		return KeyCode::None;
	}

	void Input::UpdateMouseInput()
	{
		
	}

	void Input::PollInputEvents()
	{
		POINT currentMousePosition = {};
		GetCursorPos(&currentMousePosition);

		s_CurrentMousePosition = Vector2Int(currentMousePosition.x,
											currentMousePosition.y);

		s_MouseInput.MousePosition = s_CurrentMousePosition;

		if (s_CurrentMousePosition.x != s_PrevMousePosition.x ||
			s_CurrentMousePosition.y != s_PrevMousePosition.y)
		{
			s_MouseInput.DeltaMousePosition = s_CurrentMousePosition - s_PrevMousePosition;
			s_MouseInput.State              = MouseState::Moved;
			s_MouseInput.Button             = MouseButton::None;
		}
		else
		{
			s_MouseInput.DeltaMousePosition = Vector2Int();
		}

		if (GetKeyboardState(s_CurrentKeyState))
		{
			for (auto i = 0U; i < 256U; i++)
			{
				if (s_CurrentKeyState[i] & KEY_STATE_FLAG) // If this key state is toggled
				{
					// If not previously toggled
					// Update Keyboard and Mouse Input

					// Button and Key must be down
					if (i == VK_LBUTTON)
					{
						s_MouseInput.Button = MouseButton::LeftButton;
						s_MouseInput.State  = MouseState::ButtonPressed;
					}
					else if (i == VK_RBUTTON)
					{
						s_MouseInput.Button = MouseButton::RightButton;
						s_MouseInput.State  = MouseState::ButtonPressed;
					}
					else if (i == VK_MBUTTON)
					{
						s_MouseInput.Button = MouseButton::MiddleButton;
						s_MouseInput.State  = MouseState::ButtonPressed;
					}
					else
					{
						s_KeyInput.KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
						s_KeyInput.KeyState = KeyState::KeyDown;
					}
				}
				else
				{
					// If this key state is untoggled

					// If this key state was previously toggled
					if (s_CurrentKeyState[i] != s_PrevKeyState[i])
					{
						// Button and Key must be up
						if (i == VK_LBUTTON)
						{
							s_MouseInput.Button = MouseButton::LeftButton;
							s_MouseInput.State  = MouseState::ButtonReleased;
						}
						else if (i == VK_RBUTTON)
						{
							s_MouseInput.Button = MouseButton::RightButton;
							s_MouseInput.State  = MouseState::ButtonReleased;
						}
						else if (i == VK_MBUTTON)
						{
							s_MouseInput.Button = MouseButton::MiddleButton;
							s_MouseInput.State  = MouseState::ButtonReleased;
						}
						else
						{
							s_KeyInput.KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
							s_KeyInput.KeyState = KeyState::KeyUp;
						}
					}
				}
			}
			memcpy(s_PrevKeyState, s_CurrentKeyState, sizeof(unsigned char) * 256);
		}
		else
		{
			s_KeyInput.KeyState = KeyState::None;
			s_MouseInput.Button = MouseButton::None;
			s_MouseInput.State  = MouseState::None;
		}

		s_PrevMousePosition = s_CurrentMousePosition;
	}

	MouseInput Input::Mouse()
	{
		return s_MouseInput;
	}

	KeyboardInput Input::Keyboard()
	{
		return s_KeyInput;
	}
}
