#pragma once
#include "Time.h"

#include "Core.h"
#include "LayerSystem.h"

namespace Engine
{
	class Window;
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

		static void SetInitialLayers(List<Layer*> initialLayers);

		static void Start();

		static void Run();

		static void End();
		
		static void Quit();

		static double DeltaTime();

		static Window& WindowRef();

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

		Time m_Time;

		LayerSystem m_LayerSystem;

		friend class Window;
	};
}
