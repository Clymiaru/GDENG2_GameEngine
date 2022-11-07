#include <Engine/Engine.h>

#include "EditorLayer.h"


int main()
{
	using namespace Engine;

	// TODO: Window Resizing
	
	Application::SetLayers({new Editor::EditorLayer()});
	
	Application::Start(Application::Profile(
		"Editor",
		1280,
		720
	));
	
	Application::Run();
	
	Application::End();

	return 0;
}
