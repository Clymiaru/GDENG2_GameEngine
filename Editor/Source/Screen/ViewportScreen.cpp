#include "ViewportScreen.h"

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	ViewportScreen::ViewportScreen(Engine::ScreenID id) :
		AUIScreen{id, "Viewport"}
	{
		
	}
	
	ViewportScreen::~ViewportScreen()
	{
	}
	
	void ViewportScreen::DrawImpl()
	{
		ImGui::Begin(GetNameAndIDLabel());

		ImGui::Text("Placeholder");
		
		ImGui::End();
	}

}
