#include <Engine/Engine.h>

#include "EditorLayer.h"

int main()
{
	using namespace Engine;

	const Application::Specification appSpecs = Application::Specification{
		"Editor",
		1280,
		720,
		List<Layer*>
		{
			new Editor::EditorLayer()
			// ,new Editor::EditorUILayer()
		}
	};

	Application* app = new Application(appSpecs);

	app->Run();

	delete app;

	return 0;
}
