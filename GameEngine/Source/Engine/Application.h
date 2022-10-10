#pragma once
#include "Window.h"

#include "Utils/DataStructures.h"
#include "Utils/Pointers.h"

namespace Engine
{
	class Layer;

	class Application final
	{
	public:
		struct Profile
		{
			std::wstring Name;
			Uint Width;
			Uint Height;
		};
		
		~Application();

		static void Start(const Profile& profile);

		static void Run();

		static void Close();
		
		static void Quit();

		static void RegisterLayer(Layer* layer);

		static void DeregisterLayer(Layer* layer);

		static RECT GetClientWindowRect();

	private:
		explicit Application();

		void StartingSystems();

		void ClosingSystems();

		//--------- APP LOOP
		void Update();

		void PollEvents();

		void Render();
		//----------

		static Application m_Instance;

		UniquePtr<Profile> m_Profile;

		bool m_IsRunning;

		UniquePtr<Window> m_Window;

		List<Layer*> m_Layers;

		friend class Window;
	};
}
