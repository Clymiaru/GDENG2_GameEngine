#include "pch.h"
#include "Input.h"

#include <Windows.h>

#include "Engine/Core/Debug.h"
#include "Engine/Math/Math.h"

namespace Engine
{
	Input* Input::s_Instance = nullptr;

	Input::Input() :
		m_CurrentMousePosition{Vector2Int()},
		m_PrevMousePosition{Vector2Int()}
	{
		Debug::Assert(s_Instance == nullptr,
		              "There can only be 1 Input instantiated at any time!");
		s_Instance = this;
	}

	Input::~Input()
	{
		s_Instance = nullptr;
	}

	KeyCode TranslateVirtualKeyCodeToKeyCode(unsigned char vkCode)
	{
		if (vkCode >= 'A' && vkCode <= 'Z' ||
		    vkCode >= '0' && vkCode <= '9' ||
		    vkCode == ' ')
		{
			return (KeyCode)vkCode;
		}
		return KeyCode::None;
	}

	void Input::PollInputEvents()
	{
		POINT currentMousePosition = {};
		GetCursorPos(&currentMousePosition);
		m_CurrentMousePosition = Vector2Int(currentMousePosition.x,
		                                    currentMousePosition.y);

		m_MouseInput.MousePosition = m_CurrentMousePosition;

		if (m_CurrentMousePosition.x != m_PrevMousePosition.x ||
		    m_CurrentMousePosition.y != m_PrevMousePosition.y)
		{
			m_MouseInput.DeltaMousePosition = m_CurrentMousePosition - m_PrevMousePosition;
		}
		else
		{
			m_MouseInput.DeltaMousePosition = Vector2Int();
		}

		if (GetKeyboardState(m_CurrentKeyState))
		{
			for (auto i = 0U; i < 256U; i++)
			{
				if (m_CurrentKeyState[i] & KEY_STATE_FLAG) // If this key state is toggled
				{
					// If not previously toggled
					// Update Keyboard and Mouse Input

					// Button and Key must be down
					if (i == VK_LBUTTON)
					{
						m_MouseInput.Button = MouseButton::LeftButton;
						m_MouseInput.State  = MouseState::ButtonPressed;
					}
					else if (i == VK_RBUTTON)
					{
						m_MouseInput.Button = MouseButton::RightButton;
						m_MouseInput.State  = MouseState::ButtonPressed;
					}
					else if (i == VK_MBUTTON)
					{
						m_MouseInput.Button = MouseButton::MiddleButton;
						m_MouseInput.State  = MouseState::ButtonPressed;
					}
					else
					{
						m_KeyInput.KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
						m_KeyInput.KeyState = KeyState::KeyDown;
					}
				}
				else
				{
					// If this key state is untoggled

					// If this key state was previously toggled
					if (m_CurrentKeyState[i] != m_PrevKeyState[i])
					{
						// Button and Key must be up
						if (i == VK_LBUTTON)
						{
							m_MouseInput.Button = MouseButton::LeftButton;
							m_MouseInput.State  = MouseState::ButtonReleased;
						}
						else if (i == VK_RBUTTON)
						{
							m_MouseInput.Button = MouseButton::RightButton;
							m_MouseInput.State  = MouseState::ButtonReleased;
						}
						else if (i == VK_MBUTTON)
						{
							m_MouseInput.Button = MouseButton::MiddleButton;
							m_MouseInput.State  = MouseState::ButtonReleased;
						}
						else
						{
							m_KeyInput.KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
							m_KeyInput.KeyState = KeyState::KeyUp;
						}
					}
				}
			}
			memcpy(m_PrevKeyState, m_CurrentKeyState, sizeof(unsigned char) * 256);
		}
		else
		{
			m_KeyInput.KeyState = KeyState::None;
			m_MouseInput.Button = MouseButton::None;
			m_MouseInput.State  = MouseState::None;
		}

		m_PrevMousePosition = m_CurrentMousePosition;
	}

	MouseInput Input::Mouse()
	{
		return s_Instance->m_MouseInput;
	}

	KeyboardInput Input::Keyboard()
	{
		return s_Instance->m_KeyInput;
	}
}
