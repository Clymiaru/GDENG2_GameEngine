#include "pch.h"
#include "InputHandler.h"

#include <Windows.h>

#include "Engine/Core/Debug.h"
#include "Engine/Math/Vector2.h"

void Engine::InputHandler::Start()
{
	m_EventMap[Event::Type::Key]   = new KeyEvent();
	m_EventMap[Event::Type::Mouse] = new MouseEvent();
}

void Engine::InputHandler::End()
{
	m_EventMap.clear();
}

Engine::KeyCode TranslateVirtualKeyCodeToKeyCode(unsigned char vkCode)
{
	if (vkCode >= 'A' && vkCode <= 'Z' ||
	    vkCode >= '0' && vkCode <= '9')
	{
		return (Engine::KeyCode)vkCode;
	}
	return Engine::KeyCode::None;
}

void Engine::InputHandler::PollInputEvents()
{
	POINT currentMousePosition = {};
	GetCursorPos(&currentMousePosition);
	m_CurrentMousePosition = Vector2Int(currentMousePosition.x, currentMousePosition.y);

	MouseEvent* mouseEvent         = (MouseEvent*)m_EventMap[Event::Type::Mouse];
	mouseEvent->MousePosition      = m_CurrentMousePosition;
	mouseEvent->DeltaMousePosition = Vector2Int(0, 0);

	if (m_CurrentMousePosition.x != m_PrevMousePosition.x ||
	    m_CurrentMousePosition.y != m_PrevMousePosition.y)
	{
		mouseEvent->DeltaMousePosition = m_CurrentMousePosition - m_PrevMousePosition;
		mouseEvent->State              = MouseState::Moved;
		mouseEvent->Button             = MouseButton::None;
	}

	KeyEvent* keyEvent = (KeyEvent*)m_EventMap[Event::Type::Key];

	if (GetKeyboardState(m_CurrentKeyState))
	{
		for (auto i = 0U; i < 256U; i++)
		{
			if (m_CurrentKeyState[i] & KEY_STATE_FLAG)
			{
				if (m_CurrentKeyState[i] != m_PrevKeyState[i])
				{
					if (i == VK_LBUTTON)
					{
						mouseEvent->Button = MouseButton::LeftButton;
						mouseEvent->State  = MouseState::ButtonPressed;
					}
					else if (i == VK_RBUTTON)
					{
						mouseEvent->Button = MouseButton::RightButton;
						mouseEvent->State  = MouseState::ButtonPressed;
					}
					else
					{
						keyEvent->KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
						keyEvent->KeyState = KeyState::KeyDown;
					}
				}
			}
			else
			{
				if (m_CurrentKeyState[i] != m_PrevKeyState[i])
				{
					if (i == VK_LBUTTON)
					{
						mouseEvent->Button = MouseButton::LeftButton;
						mouseEvent->State  = MouseState::ButtonReleased;
					}
					else if (i == VK_RBUTTON)
					{
						mouseEvent->Button = MouseButton::RightButton;
						mouseEvent->State  = MouseState::ButtonReleased;
					}
					else
					{
						keyEvent->KeyCode  = TranslateVirtualKeyCodeToKeyCode(i);
						keyEvent->KeyState = KeyState::KeyUp;
					}
				}
			}
		}
		memcpy(m_PrevKeyState, m_CurrentKeyState, sizeof(unsigned char) * 256);
	}
	else
	{
		keyEvent->KeyState = KeyState::None;
		mouseEvent->Button = MouseButton::None;
		mouseEvent->State  = MouseState::None;
	}

	m_PrevMousePosition = m_CurrentMousePosition;
}

Engine::KeyEvent& Engine::InputHandler::ActiveKeyInput()
{
	return *((KeyEvent*)m_EventMap[Event::Type::Key]);
}

Engine::MouseEvent& Engine::InputHandler::ActiveMouseInput()
{
	return *((MouseEvent*)m_EventMap[Event::Type::Mouse]);
}
