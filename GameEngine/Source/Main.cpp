#include "pch.h"

#include "Editor/EditorLayer.h"

#include "Engine/Application.h"

auto main() -> int
{
	Engine::Application::RegisterLayer(new Editor::EditorLayer());
	Engine::Application::Run({L"Editor", 1280, 720});
	PostQuitMessage(0);
	return 0;
}
