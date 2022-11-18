#pragma once
#include "Time.h"

#include "Core.h"
#include "Window.h"
#include "LayerSystem.h"

namespace Engine {
	class ComponentSystemHandler;
}
namespace Engine
{
	class Window;
	class Input;
	class ResourceSystem;
	class UISystem;

	class Renderer;
	class Layer;
	class LayerSystem;
	class EntityManager;

	class Application final
	{
	public:
		struct Specification
		{
			String Name                      = "Untitled";
			unsigned int InitialWindowWidth  = 0;
			unsigned int InitialWindowHeight = 0;
			List<Layer*> InitialLayers       = List<Layer*>();
		};

		struct Profile
		{
			bool IsRunning       = false;
			String AssetDataPath = "Assets/";
			TimeData Time        = TimeData();
		};

		explicit Application(const Specification& specs);

		~Application();

		static Profile GetInfo();

		static Window::Profile GetWindowInfo();

		static Renderer& GetRenderer();

		void Run();

		Application(const Application&)                = delete;
		Application& operator=(const Application&)     = delete;
		Application(Application&&) noexcept            = delete;
		Application& operator=(Application&&) noexcept = delete;

	private:
		void Start();

		void End();

		//--------------------------------//
		// APP LOOP                       //
		//--------------------------------//
		void Update() const;

		void PollEvents() const;

		void Render() const;
		//--------------------------------//

		//--------------------------------//
		// WINDOW EVENTS                  //
		//--------------------------------//
		bool OnWindowClose(AEvent* e);
		bool OnWindowResize(AEvent* e);
		bool OnWindowFocus(AEvent* e);
		bool OnWindowUnfocus(AEvent* e);

		Specification m_Specs;

		Profile m_Profile;

		// Systems

		Window* m_Window;

		SwapChain* m_SwapChain;

		Timer* m_Timer;

		Input* m_Input;

		ResourceSystem* m_ResourceSystem;

		Renderer* m_Renderer;

		UISystem* m_UISystem;

		EntityManager* m_EntityManager;

		ComponentSystemHandler* m_ComponentSystemHandler;
		
		LayerSystem* m_LayerSystem;

		// EntityManager* m_EntityManager;

		static Application* s_Instance;
	};
}
