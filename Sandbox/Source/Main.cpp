#include "Engine/Engine.h"

#include "SandboxLayer.h"

#include <Engine/Core/Application.h>

void testing()
{
	static int i = 4;
	Engine::Debug::Log("Testing {0} {1} {0}", 1, 5);

	Engine::Debug::Log(L"Testing Wide {0} {1} {0}", 1, 5);
	Engine::Debug::Assert(i == 2, "i is not 4 {0}", "Testing A");
}
int main()
{
	using namespace Engine;

	testing();
	
	Application::SetLayers({new Sandbox::SandboxLayer()});
	
	Application::Start(Application::Profile(
		L"Sandbox",
		1280,
		720
	));
	
	Application::Run();
	
	Application::End();

	return 0;
}
