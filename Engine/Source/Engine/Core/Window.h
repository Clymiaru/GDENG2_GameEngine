#pragma once
#include <Windows.h>

#include "Core.h"

#include "Engine/Math/Rect.h"
#include "Engine/Math/Vector2.h"

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
				Name{L"Unnamed"},
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

		Window();

		~Window();

		void PollEvents();

		void Start(const Profile& profile);

		void Close();

		HWND& GetHandle();

		Rect<uint32_t>& WindowRect();

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
