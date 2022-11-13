#include "PlaceholderHUD.h"

#include <Engine/Core/Core.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	PlaceholderHUD::PlaceholderHUD() :
		AUIScreen{"PlaceholderHUD"},
		m_IsOpen{false},
		m_ColorPickerHUD{nullptr}
	{
		m_ColorPickerHUD = new ColorPickerHUD();
	}

	PlaceholderHUD::~PlaceholderHUD()
	{
		delete m_ColorPickerHUD;
	}

	void PlaceholderHUD::Open()
	{
		m_IsOpen = true;
	}

	void PlaceholderHUD::Close()
	{
		m_IsOpen = false;
	}

	void PlaceholderHUD::DrawImpl()
	{
		Engine::String uiTag = m_Name;
		uiTag += "##MainMenuBar2";

		if (m_IsOpen == false)
			return;

		if (!ImGui::Begin(uiTag.c_str(), &m_IsOpen))
		{
			ImGui::End();
		}
		else
		{
			if (ImGui::Button("Create Color Picker##PlaceholderHUD"))
			{
				m_ColorPickerHUD->Open();
			}

			ImGui::End();
		}

		m_ColorPickerHUD->Draw();
	}
}
