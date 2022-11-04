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
		ImGui::Text("Scene Editor Version: 0.01");
		ImGui::Text("Developer: Lanz Santiago");
		ImGui::Separator();
		ImGui::Text("Special Thanks");
		ImGui::Text("Sir Neil");
		ImGui::Text("Pardcode (https://www.youtube.com/c/PardCode)");
		ImGui::Text("Cherno (https://www.youtube.com/c/TheChernoProject)");
		ImGui::Text("ChiliTomatoNoodle (https://www.youtube.com/c/ChiliTomatoNoodle)");
		ImGui::Text("Stack Overflow ;)");
	}
}

