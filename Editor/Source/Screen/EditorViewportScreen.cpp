#include "EditorViewportScreen.h"
#include <Engine/ECS/Entity/EditorCamera.h>
#include <format>
#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	EditorViewportScreen::EditorViewportScreen(const Engine::ScreenID id,
	                               Engine::EditorCamera* editorCamera) :
		AUIScreen{id, "Viewport"},
		m_EditorCameraRef{editorCamera} { }

	EditorViewportScreen::~EditorViewportScreen() { }

	void EditorViewportScreen::DrawImpl()
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
