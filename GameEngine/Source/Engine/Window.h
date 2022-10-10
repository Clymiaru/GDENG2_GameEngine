#pragma once
#include <Windows.h>
#include <string>

#include "Utils/Math.h"

namespace Engine
{
	class Application;

	class Window final
	{
	public:
		struct Profile
		{
			std::wstring Name;

			Uint Width;

			Uint Height;
		};

		Window(Profile profile);

		~Window() = default;

		[[nodiscard]]
		RECT GetClientWindowRect() const;

		[[nodiscard]]
		HWND GetHandle() const;

		void SetHandle(HWND handle);

	private:
		void Start();

		void PollEvents();

		void Close();

		HWND Create(Profile profile);

		HWND m_Handle;

		Profile m_Profile;

		MSG m_Message;

		friend class Application;
	};
}
