#include "CreditsScreen.h"

#include <Engine/Core/Debug.h>
#include <d3d11.h>

#include <Engine/Graphics/Renderer.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"



namespace Editor
{
	CreditsScreen::CreditsScreen() :
		AUIScreen{"Credits"},
		m_IsOpen{false}
	{
		LoadTextureFromFile("Assets/DLSU_Logo.png", &m_TextureView, &m_ImageWidth, &m_ImageHeight);
	}

	CreditsScreen::~CreditsScreen() = default;

	void CreditsScreen::Open()
	{
		m_IsOpen = true;
	}

	void CreditsScreen::Close()
	{
		m_IsOpen = false;
	}

	void CreditsScreen::DrawImpl()
	{
		Engine::String uiTag = m_Name;
		uiTag += "##MainMenuBar2";
		ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;

		if (m_IsOpen == false)
			return;

		if (!ImGui::Begin(uiTag.c_str(), &m_IsOpen))
		{
			ImGui::End();
		}
		else
		{
			float imageRatio = (float)m_ImageWidth / (float)m_ImageHeight;
			ImGui::Image(m_TextureView, ImVec2(256 * imageRatio, 256 * imageRatio));
			ImGui::Spacing();

			ImGui::Text("Scene Editor Version: 0.01");
			ImGui::Text("Developer: Lanz Joseph I. Santiago");
			ImGui::Separator();

			ImGui::Text("Special Thanks");
			ImGui::Text("Sir Neil's GDENG-2 Course");
			ImGui::Text("Pardcode (https://www.youtube.com/c/PardCode)");
			ImGui::Text("Cherno (https://www.youtube.com/c/TheChernoProject)");
			ImGui::Text("ChiliTomatoNoodle (https://www.youtube.com/c/ChiliTomatoNoodle)");
			ImGui::Text("Stack Overflow ;)");
			ImGui::End();
		}
	}
}
