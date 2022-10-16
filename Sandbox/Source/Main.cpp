
#include "SandboxLayer.h"

#include "Engine/Engine.h"
int main()
{
	using namespace Engine;

	Application::SetProfile(Application::Profile(
		L"Sandbox",
		1280,
		720
	));

	Application::SetInitialLayers({new Sandbox::SandboxLayer()});

	Application::Start();

	Application::Run();

	Application::End();

	return 0;
}
