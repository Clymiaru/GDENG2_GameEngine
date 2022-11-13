#include "ColorPickerHUD.h"

#include <Engine/Math/Math.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	ColorPickerHUD::ColorPickerHUD() :
		AUIHUD{"ColorPickerPlaceholder"}
	{
	}
	
	ColorPickerHUD::~ColorPickerHUD()
	{
	}
	
	void ColorPickerHUD::Open()
	{
		m_IsOpen = true;
	}
	
	void ColorPickerHUD::Close()
	{
		m_IsOpen = false;
	}

	void ColorPickerHUD::DrawImpl()
	{
		Engine::String uiTag = m_Name;
		uiTag += "##MainMenuBar2";

		static Engine::Vector3Float color; 
		if (m_IsOpen == false)
			return;

		if (!ImGui::Begin(uiTag.c_str(), &m_IsOpen))
		{
			ImGui::End();
		}
		else
		{
			ImGui::ColorPicker3("ColorPicker##ColorPickerHUD", (float*)&color);
			
			ImGui::End();
		}
	}

}
