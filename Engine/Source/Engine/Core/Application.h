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
			String Name;
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

		Application(const Application&) = delete;
	
		Application& operator=(const Application& v) = delete;
	
		Application(Application&&) noexcept = delete;
	
		Application& operator=(Application&&) noexcept = delete;

	private:
		Application();

		~Application();

		static Application& Instance();

		void StartSystems();

		void EndSystems();

		//--------- APP LOOP
		void Update();

		void PollEvents();

		void Render();
		//----------

		Profile m_Profile;

		bool m_IsRunning;

		// Make RenderSystem not a singleton
		// Make TimeSystem not a singleton

		Window* m_Window;

		Time m_Time;

		LayerSystem m_LayerSystem;

		static Application m_Instance;

		friend class Window;
	};
}