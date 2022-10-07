#include "pch.h"

#include "Editor/EditorApplication.h"
#include "Engine/Utils/Math.h"

auto main() -> int
{
	const auto windowRect = Engine::RectUint({0, 0, 1280, 720});
	auto editorApp        = Editor::EditorApplication(windowRect);

	editorApp.Initialize();

	editorApp.Run();

	editorApp.Terminate();

	return 0;
}
