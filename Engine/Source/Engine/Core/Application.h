#pragma once
#include "Time.h"

#include "Core.h"
#include "LayerSystem.h"

namespace Engine
{
	class InputHandler;
	class Renderer;
	class Window;
	class Layer;
	class Application final
	{
	public:
		struct Profile
		{
			String Name;
			uint32_t Width;
			uint32_t Height;
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

		Window* m_Window;

		Renderer* m_Renderer;

		InputHandler* m_InputHandler;

		Time m_Time;

		LayerSystem m_LayerSystem;

		static Application m_Instance;

		friend class Window;
	};
}
