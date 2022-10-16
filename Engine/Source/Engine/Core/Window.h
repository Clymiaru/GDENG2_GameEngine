#pragma once
#include <Windows.h>

namespace Engine
{
	class Window final
	{
	public:
		struct Profile
		{
			WString Name;

			Uint Width;

			Uint Height;

			Profile() :
				Name{TEXT("Unnamed")},
				Width{640},
				Height{480}
			{
			}

			Profile(const WString name,
			        const Uint& width,
			        const Uint& height) :
				Name{name},
				Width{width},
				Height{height}
			{
			}
		};

		Window();

		~Window();

		static Window* Create(const Profile& profile);

		void PollEvents();

		void Start();

		void Close();

		HWND& GetHandle();

		Vector2 GetSize();

	private:
		void UpdateClientSize();

		HWND m_Handle;

		MSG m_Message;

		Vector2 m_ClientSize;

		friend LRESULT CALLBACK WindowsProcedure(HWND windowHandle,
		                                UINT message,
		                                WPARAM wParam,
		                                LPARAM lParam);
	};
}
