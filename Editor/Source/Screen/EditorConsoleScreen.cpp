#include "EditorConsoleScreen.h"

#include <Engine/Core/Debug.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	EditorConsoleScreen::EditorConsoleScreen(Engine::ScreenID id) :
		AUIScreen{id, "Console"}
	{}
	
	EditorConsoleScreen::~EditorConsoleScreen() = default;
	
	void EditorConsoleScreen::DrawImpl()
	{
		ImGui::Begin(GetNameAndIDLabel());

		for (auto message : Engine::Debug::g_DebugMessageHistory)
		{
			ImGui::Text(message.c_str());
		}
		
		ImGui::End();
	}

}
