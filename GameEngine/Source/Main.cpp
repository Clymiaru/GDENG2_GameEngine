#include "pch.h"

#include "Editor/EditorApplication.h"
#include "Engine/Utils/Math.h"

auto main() -> int
{
	constexpr auto appWindowSize = Engine::Vector2Int({1280, 720});
	auto editorApp = Editor::EditorApplication(appWindowSize);

	if (editorApp.Initialize())
	{
		editorApp.Run();
	}

	if (editorApp.Terminate())
	{
		std::cout << "App has an error being destroyed!\n";
	}

	return 0;
}
