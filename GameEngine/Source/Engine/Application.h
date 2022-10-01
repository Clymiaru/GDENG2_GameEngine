#pragma once
#include "Window.h"
#include "Utils/DataStructures.h"
#include "Utils/Math.h"
#include "Utils/Pointers.h"

namespace Engine
{
	struct ApplicationDescription
	{
		std::wstring ApplicationName;

		Vector2Int StartWindowSize;
	};

	class Application
	{
	public:
		explicit Application(ApplicationDescription description);

		virtual ~Application();

		auto Initialize() -> bool;

		auto Terminate() -> bool;

		auto Run() -> void;

	private:
		auto virtual InitializeSystems() -> void = 0;

		auto virtual TerminateSystems() -> void = 0;

		bool m_IsRunning;

	protected:
		ApplicationDescription m_Description;

		List<UniquePtr<Window>> m_Windows;
	};
}
