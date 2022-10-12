#include "pch.h"

#include "Engine/Application.h"

#include "Sandbox/SandboxGridLayer.h"

auto main() -> int
{
	using namespace Engine;
	
	Application::Start(Application::Profile{L"Editor", 1280, 720});

	Application::RegisterLayer(new Sandbox::SandboxGridLayer());

	Application::Run();

	Application::Close();

	return 0;
}
