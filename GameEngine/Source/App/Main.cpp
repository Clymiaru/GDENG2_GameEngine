#include <iostream>

#include "AppWindow.h"
#include "Engine/Utils/Math.h"

auto main() -> int
{
	constexpr auto appWindowSize = Engine::Vector2Int({1280, 720});
	auto app                     = App::AppWindow(L"Game Engine",
	                                              appWindowSize);
	if (app.Init())
	{
		while (app.IsRunning())
		{
			app.Broadcast();
		}
	}

	// if (!app.Release())
	// {
	// 	std::cout << "App has an error being destroyed!\n";
	// }
	
	return 0;
}
