﻿#pragma once
#include "Time.h"

#include "Core.h"
#include "Window.h"

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
		struct Specification
		{
			String Name         = "Untitled";
			unsigned int InitialWindowWidth  = 0;
			unsigned int InitialWindowHeight = 0;
			List<Layer*> InitialLayers = List<Layer*>();
		};

		struct Profile
		{
			bool IsRunning = false;
			String AssetDataPath = "Assets/";
			TimeData Time = TimeData();
		};

		explicit Application(const Specification& specs);

		~Application();

		static Profile GetInfo();

		static Window::Profile GetWindowInfo();

		bool Quit(Event* event);

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

		Specification m_Specs;

		Profile m_Profile;

		Window* m_Window;

		Timer* m_Timer;

		LayerHandler* m_LayerHandler;

		static Application* s_Instance;
	};
}
