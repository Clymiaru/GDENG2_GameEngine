#include "pch.h"
#include "AUIScreen.h"

#include "../../../Dependencies/ImGui/imgui.h"

namespace Engine
{
	AUIScreen::AUIScreen(const String& name) :
		m_Name{name}
	{
	}

	void AUIScreen::DrawImpl()
	{
		ImGui::Begin(m_Name.c_str());

		Draw();

		ImGui::End();
	}
}
