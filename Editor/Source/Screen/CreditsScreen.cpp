#include "CreditsScreen.h"

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	CreditsScreen::CreditsScreen() :
		AUIScreen{"Credits"}
	{
	}

	CreditsScreen::~CreditsScreen() = default;

	void CreditsScreen::Draw()
	{
		ImGui::Text("Text is here");
	}
}

