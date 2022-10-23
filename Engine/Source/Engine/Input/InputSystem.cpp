#include "pch.h"
#include "InputSystem.h"

#include <Windows.h>

void Engine::InputSystem::Update()
{
	if (::GetKeyboardState(m_KeyState))
	{
		for (auto i = 0U; i < 256U; i++)
		{
			if (m_KeyState[i] & 0x80)
			{
				for (auto* listener : m_Listeners)
				{
					listener->OnKeyDown(i);
				}
			}
			else
			{
				if (m_KeyState[i] != m_PrevKeyState[i])
				{
					for (auto* listener : m_Listeners)
					{
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
						
					}
					else if (i == VK_RBUTTON)
					{
						
					}
					else
						listener->OnKeyDown(i);
				}
			}
			else
			{
				if (m_KeyState[i] != m_PrevKeyState[i])
				{
					for (auto* listener : m_Listeners)
					{
						listener->OnKeyUp(i);
					}
				}
			}
		}

		memcpy(m_PrevKeyState, m_KeyState, sizeof(unsigned char) * 256);
		
	}
}
