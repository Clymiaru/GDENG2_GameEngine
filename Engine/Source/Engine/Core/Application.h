#pragma once
#include "Time.h"

#include "Core.h"

#include "Engine/Math/Rect.h"

namespace Engine
{
	class Input;
	class Renderer;
	class Window;
	class Layer;
	class LayerHandler;
	class Application final
	{
	public:
		struct Profile
		{
			String Name = "Untitled";
			uint32_t Width = 0;
			uint32_t Height = 0;
		};

		static void SetLayers(List<Layer*> initialLayers);

		static void Start(const Profile& profile);

		static void Run();

		static void End();
		
		static void Quit();

		static double DeltaTime();

		static Rect<uint32_t> WindowRect();

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
		void Update() const;

		void PollEvents() const;

		void Render() const;
		//----------

		bool m_IsRunning;

		UniquePtr<Window> m_Window;

		Time m_Time;

		UniquePtr<LayerHandler> m_LayerHandler;

		static Application m_Instance;

		friend class Window;
	};
}
