#include "pch.h"
#include "InputSystem.h"

#include <Windows.h>

void Engine::InputSystem::Update()
{
	POINT currentMousePosition = {};
	::GetCursorPos(&currentMousePosition);

	if (m_IsFirstTime)
	{
		m_PrevMousePosition = Vector2(currentMousePosition.x, currentMousePosition.y);
		m_IsFirstTime  = false;
	}

	if (currentMousePosition.x != static_cast<Uint>(m_PrevMousePosition.X()) ||
	    currentMousePosition.y != static_cast<Uint>(m_PrevMousePosition.Y()))
	{
		for (auto* listener : m_Listeners)
		{
			Vector2 mousePos = Vector2(currentMousePosition.x - static_cast<Uint>(m_PrevMousePosition.X()),
			                           currentMousePosition.y - static_cast<Uint>(m_PrevMousePosition.Y()));
			listener->OnMouseMove(mousePos);
		}
	}
	m_PrevMousePosition = Vector2(currentMousePosition.x, currentMousePosition.y);

	if (::GetKeyboardState(m_KeyState))
	{
		for (auto i = 0U; i < 256U; i++)
		{
			if (m_KeyState[i] & 0x80)
			{
				for (auto* listener : m_Listeners)
				{
					if (i == VK_LBUTTON)
					{
						if (m_KeyState[i] != m_PrevKeyState[i])
							listener->OnLeftMouseButtonDown(Vector2(currentMousePosition.x, currentMousePosition.y));
					}
					else if (i == VK_RBUTTON)
					{
						if (m_KeyState[i] != m_PrevKeyState[i])
							listener->OnRightMouseButtonDown(Vector2(currentMousePosition.x, currentMousePosition.y));
					}
					else
						listener->OnKeyDown(i);
				}
			}
			else
			{
				if (m_KeyState[i] != m_PrevKeyState[i])
				{
					// Wouldn't this get received by everyone listening without consideration of
					// whether they should receive it or not
					// i.e. UI overlay should recevie the mouse button down while the game
					// view shouldn't
					for (auto* listener : m_Listeners)
					{
						if (i == VK_LBUTTON)
						{
							if (m_KeyState[i] != m_PrevKeyState[i])
								listener->OnLeftMouseButtonUp(Vector2(currentMousePosition.x, currentMousePosition.y));
						}
						else if (i == VK_RBUTTON)
						{
							if (m_KeyState[i] != m_PrevKeyState[i])
								listener->OnRightMouseButtonUp(Vector2(currentMousePosition.x, currentMousePosition.y));
						}
						listener->OnKeyUp(i);
					}
				}
			}
		}

		memcpy(m_PrevKeyState, m_KeyState, sizeof(unsigned char) * 256);
	}
}

void Engine::InputSystem::AddListener(IInputListener* inputListener)
{
	Debug::Log("Input listener added");
	m_Listeners.insert(inputListener);
}

void Engine::InputSystem::RemoveListener(IInputListener* inputListener)
{
	Debug::Log("Input listener removed");
	m_Listeners.erase(inputListener);
}

Engine::InputSystem& Engine::InputSystem::Instance()
{
	static InputSystem instance;
	return instance;
}

void Engine::InputSystem::PollInputEvents()
{
	//TODO: Issue all inputs are applied to every listener
	// if (::GetKeyboardState(m_KeyState))
	// {
	// 	for (auto i = 0U; i < 256U; i++)
	// 	{
	// 		if (m_KeyState[i] & 0x80)
	// 		{
	// 			for (auto* listener : m_Listeners)
	// 			{
	// 				if (i == VK_LBUTTON)
	// 				{
	// 				}
	// 				else if (i == VK_RBUTTON)
	// 				{
	// 				}
	// 				else
	// 					listener->OnKeyDown(i);
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (m_KeyState[i] != m_PrevKeyState[i])
	// 			{
	// 				for (auto* listener : m_Listeners)
	// 				{
	// 					if (i == VK_LBUTTON)
	// 					{
	// 					}
	// 					else if (i == VK_RBUTTON)
	// 					{
	// 					}
	// 					else
	// 						listener->OnKeyDown(i);
	// 				}
	// 			}
	// 		}
	// 	}
	//
	// 	memcpy(m_PrevKeyState, m_KeyState, sizeof(unsigned char) * 256);
	//}
}
