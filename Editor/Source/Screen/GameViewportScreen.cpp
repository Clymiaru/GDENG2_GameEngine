#include "GameViewportScreen.h"

#include <format>

#include <Engine/Core/Application.h>
#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	GameViewportScreen::GameViewportScreen(const Engine::ScreenID id) :
		AUIScreen{id, "Game Viewport"},
		m_ViewportSize{512, 512} { }

	GameViewportScreen::~GameViewportScreen() { }

	void GameViewportScreen::DrawImpl()
	{
		using namespace Engine;

		auto gameCameraComponent = Application::GetComponentSystem().GetCameraSystem().GetGameCamera();
		
		ImGui::Begin(GetNameAndIDLabel());

		auto displaySize = ImGui::GetContentRegionAvail();
		m_ViewportSize.x = displaySize.x;
		m_ViewportSize.y = displaySize.y;

		if (gameCameraComponent == nullptr)
		{
			ImGui::End();
			return;
		}

		auto& renderTarget       = gameCameraComponent->GetRenderTarget();
		ImGui::Image(&renderTarget.GetFrame(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));
		
		ImGui::End();
	}
}
