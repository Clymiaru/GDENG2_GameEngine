#pragma once
#include <Windows.h>

#include "Core.h"

#include "Engine/Math/Rect.h"

namespace Engine
{
	class Window final
	{
	public:
		struct Profile
		{
			String Name;

			uint32_t Width;

			uint32_t Height;

			Profile() :
				Name{"Unnamed"},
				Width{640},
				Height{480}
			{
			}

			Profile(const StringView name,
					const uint32_t& width,
					const uint32_t& height) :
				Name{name},
				Width{width},
				Height{height}
			{
			}
		};

		explicit Window(const Profile& profile);

		~Window();

		void PollEvents();

		HWND& GetHandle();

		Rect<uint32_t>& WindowRect();

		Window(const Window&) = delete;
	
		Window& operator=(const Window&) = delete;
	
		Window(Window&&) noexcept = delete;
	
		Window& operator=(Window&&) noexcept = delete;

	private:
		void UpdateClientSize();

		HWND m_Handle;

		MSG m_Message;

		Rect<uint32_t> m_ClientRect;

		friend LRESULT CALLBACK WindowsProcedure(HWND windowHandle,
										UINT message,
										WPARAM wParam,
										LPARAM lParam);
	};
}
