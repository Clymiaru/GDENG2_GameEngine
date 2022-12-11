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

		if (gameCameraComponent == nullptr)
		{
			return;
		}

		auto* renderTarget = &gameCameraComponent->GetRenderTarget();

		if ((m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f) &&
		    (m_ViewportSize.x != renderTarget->GetInfo().Width ||
		     m_ViewportSize.y != renderTarget->GetInfo().Height))
		{
			gameCameraComponent->SetSize(m_ViewportSize.x, m_ViewportSize.y);
			renderTarget = &gameCameraComponent->GetRenderTarget();
		}

		ImGui::Begin(GetNameAndIDLabel());

		ImVec2 displaySize = ImGui::GetContentRegionAvail();
		m_ViewportSize.x   = (uint32_t)displaySize.x;
		m_ViewportSize.y   = (uint32_t)displaySize.y;

		ImGui::Image(&renderTarget->GetFrame(),
		             ImVec2((float)m_ViewportSize.x,
		                    (float)m_ViewportSize.y));

		ImGui::End();
	}
}
