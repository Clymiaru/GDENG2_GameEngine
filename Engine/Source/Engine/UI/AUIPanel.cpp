#include "pch.h"
#include "AUIPanel.h"

#include "../../../Dependencies/ImGui/imgui.h"

namespace Engine
{
	AUIPanel::AUIPanel(const String& name) :
		m_Name{name}
	{
	}

	void AUIPanel::Draw()
	{
		ImGui::Begin(m_Name.c_str());
		DrawImpl();
		ImGui::End();
	}

	void AUIPanel::DrawImpl()
	{
		
	}
}
