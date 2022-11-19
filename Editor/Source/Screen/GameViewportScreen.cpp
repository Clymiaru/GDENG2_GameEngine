#include "GameViewportScreen.h"

#include <format>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	GameViewportScreen::GameViewportScreen(const Engine::ScreenID id) :
		AUIScreen{id, "Viewport"} { }

	GameViewportScreen::~GameViewportScreen() { }

	void GameViewportScreen::DrawImpl()
	{
		using namespace Engine;
		
		ImGui::Begin(GetNameAndIDLabel());

		auto displaySize = ImGui::GetContentRegionAvail();

		const String windowSizeText = std::vformat("Viewport Size: {0}x{1}",
												   std::make_format_args(displaySize.x, displaySize.y));

		ImGui::Text(windowSizeText.c_str());

		ImGui::End();
	}
}
