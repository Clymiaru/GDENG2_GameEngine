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
		~Application();

		//For now until there is a preferable way
		static auto Run(Window::Profile windowProfile) -> void;
		
		static auto Quit() -> void;

		static auto RegisterLayer(Layer* layer) -> void;

		static auto DeregisterLayer(Layer* layer) -> void;

		static auto GetClientWindowRect() -> RECT;

	private:
		explicit Application();

		//For now until there is a preferable way
		auto Start(Window::Profile windowProfile) -> void;

		auto Close() -> void;
		
		auto StartingSystems() -> void;

		auto ClosingSystems() -> void;

		auto Update() -> void;

		auto PollEvents() -> void;

		auto Render() -> void;

		static Application m_Instance;

		bool m_IsRunning;

		UniquePtr<Window> m_Window;

		List<Layer*> m_Layers;
	};
}
