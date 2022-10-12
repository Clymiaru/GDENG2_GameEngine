#include "pch.h"

#include "Editor/AnimQuadLayer.h"
#include "Editor/EditorLayer.h"
#include "Engine/Application.h"

#include "Sandbox/SandboxGridLayer.h"

auto main() -> int
{
	//Engine::Application::RegisterLayer(new Editor::EditorLayer());

	//Engine::Application::RegisterLayer(new Editor::AnimQuadLayer());

	using namespace Engine;
	
	Application::Start(Application::Profile{L"Editor", 1280, 720});

	Application::RegisterLayer(new Editor::AnimQuadLayer());

	Application::Run();

	Application::Close();

	return 0;
}
