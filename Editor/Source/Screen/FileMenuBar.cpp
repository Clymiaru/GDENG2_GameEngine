#include "FileMenuBar.h"

#include <Engine/UI/UISystem.h>

#include "EntityInspectorScreen.h"
#include "ViewportScreen.h"
#include "WorldOutlinerScreen.h"

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	FileMenuBar::FileMenuBar(Engine::ScreenID id,
	                         WorldOutlinerScreen& worldOutlinerScreenRef) :
		AUIScreen{id, "File Menu Bar"},
		m_WorldOutlinerScreenRef{worldOutlinerScreenRef} { }

	FileMenuBar::~FileMenuBar() { }

	void FileMenuBar::DrawImpl()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Inspector"))
				{
					Engine::UISystem::Create<EntityInspectorScreen>(m_WorldOutlinerScreenRef);
				}

				if (ImGui::MenuItem("Scene Viewport"))
				{
					Engine::UISystem::Create<ViewportScreen>();
				}

				if (ImGui::MenuItem("Game Viewport"))
				{
					Engine::UISystem::Create<ViewportScreen>();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("About"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}
