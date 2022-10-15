#pragma once

#include "Core.h"
#include "Window.h"

namespace Engine
{
	class Layer;
	
	class Application final
	{
	public:
		struct Profile
		{
			WString Name;
			Uint Width{};
			Uint Height{};
		};

		static void SetProfile(const Profile& profile);

		static void Start();

		static void Run();

		static void End();
		
		static void Quit();

	private:
		Application();

		~Application();

		static Application& Instance();

		void StartingSystems();

		void EndingSystems();

		//--------- APP LOOP
		void Update();

		void PollEvents();

		void Render();
		//----------

		Profile m_Profile;

		bool m_IsRunning;

		Window* m_Window;

		friend class Window;
	};
}
