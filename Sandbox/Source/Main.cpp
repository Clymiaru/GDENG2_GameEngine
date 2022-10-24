// #include "Engine/Engine.h"
//
// #include "SandboxLayer.h"

#include <iostream>

#include "Engine/Core/Math.h"
int main()
{
	Engine::Vector2<float> v1 = Engine::Vector2<float>(2.0f, 2.0f);
	Engine::Vector2<float> v2 = Engine::Vector2<float>{1.0f, 1.0f};

	Engine::Vector2<float> v3 = v1 + v2;
	std::cout << v3.x << "\n";
	
	
	// using namespace Engine;
	//
	// Application::SetProfile(Application::Profile(
	// 	L"Sandbox",
	// 	1280,
	// 	720
	// ));
	//
	// Application::SetInitialLayers({new Sandbox::SandboxLayer()});
	//
	// Application::Start();
	//
	// Application::Run();
	//
	// Application::End();

	return 0;
}
