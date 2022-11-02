#include "Engine/Engine.h"

#include "SandboxLayer.h"

#include <Engine/Core/Application.h>

int main()
{
	using namespace Engine;

	Application::SetLayers({new Sandbox::SandboxLayer()});
	
	Application::Start(Application::Profile(
		"Sandbox",
		1280,
		720
	));
	
	Application::Run();
	
	Application::End();

	return 0;
}
