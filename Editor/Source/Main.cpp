#include "EditorLayer.h"

#include "Engine/Engine.h"

int main()
{
	using namespace Engine;

	// TODO: Window Resizing
	
	Application::SetLayers({new Editor::EditorLayer()});
	
	Application::Start(Application::Profile(
		L"Editor",
		1280,
		720
	));
	
	Application::Run();
	
	Application::End();

	return 0;
}
