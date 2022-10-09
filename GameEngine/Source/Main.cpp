#include "pch.h"

#include "Editor/AnimQuadLayer.h"
#include "Editor/EditorLayer.h"

#include "Engine/Application.h"

#include "Sandbox/SandboxGridLayer.h"

auto main() -> int
{
	//Engine::Application::RegisterLayer(new Editor::EditorLayer());

	//Engine::Application::RegisterLayer(new Sandbox::SandboxGridLayer());

	Engine::Application::RegisterLayer(new Editor::AnimQuadLayer());
	Engine::Application::Run({L"Editor", 1280, 720});
	PostQuitMessage(0);
	return 0;
}
