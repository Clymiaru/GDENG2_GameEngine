#pragma once
#include "Window.h"

#include "Graphics/RenderSystem.h"

#include "Utils/Math.h"
#include "Utils/Pointers.h"

namespace Engine
{
	struct ApplicationDescription
	{
		std::wstring ApplicationName;
		RectUint StartWindowRect;
	};

	class Application
	{
	public:
		explicit Application(ApplicationDescription description);

		virtual ~Application();

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto Run() -> void;

	private:
		auto virtual InitializeSystems() -> void = 0;

		auto virtual TerminateSystems() -> void = 0;

		bool m_IsRunning;

	protected:
		ApplicationDescription m_Description;

		UniquePtr<Window> m_Window;
	};
}
