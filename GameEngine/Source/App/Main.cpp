#include "AppWindow.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Debug.h"
int main()
{
	const auto APP_WINDOW_SIZE = Engine::Vector2Int({ 1280, 720 });

	auto app = App::AppWindow(L"Game Engine", 
							  APP_WINDOW_SIZE);

	if (app.Init())
	{
		while (app.IsRunning())
		{
			app.Broadcast();
		}
	}
}