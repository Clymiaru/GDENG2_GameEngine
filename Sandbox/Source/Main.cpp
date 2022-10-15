#include "pch.h"

#include "Engine/Engine.h"

int main()
{
	using namespace Engine;

	Application::SetProfile(Application::Profile{
		L"Sandbox",
		1280,
		720
	});

	Application::Start();

	Application::Run();

	Application::End();

	return 0;
}