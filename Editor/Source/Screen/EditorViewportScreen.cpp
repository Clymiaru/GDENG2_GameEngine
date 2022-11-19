#include "EditorViewportScreen.h"
#include <Engine/ECS/Entity/EditorCamera.h>
#include <format>

#include <Engine/ECS/Component/EditorCameraComponent.h>

#include "../../../Engine/Dependencies/ImGui/imgui.h"

namespace Editor
{
	EditorViewportScreen::EditorViewportScreen(const Engine::ScreenID id,
	                                           Engine::EditorCamera* editorCamera) :
		AUIScreen{id, "Editor Viewport"},
		m_EditorCameraRef{editorCamera},
		m_ViewportSize{512, 512}
	{ }

	EditorViewportScreen::~EditorViewportScreen() { }

	void EditorViewportScreen::DrawImpl()
	{
		using namespace Engine;

		auto editorCameraComponent = m_EditorCameraRef->GetComponent<EditorCameraComponent>();
		auto* renderTarget = &editorCameraComponent->GetRenderTarget();

		if ((m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f) &&
			(m_ViewportSize.x != renderTarget->GetInfo().Width ||
			m_ViewportSize.y != renderTarget->GetInfo().Height))
		{
			editorCameraComponent->SetSize(m_ViewportSize.x, m_ViewportSize.y);
			renderTarget = &editorCameraComponent->GetRenderTarget();
		}

		ImGui::Begin(GetNameAndIDLabel());

		auto displaySize = ImGui::GetContentRegionAvail();
		m_ViewportSize.x = displaySize.x;
		m_ViewportSize.y = displaySize.y;

		ImGui::Image(&renderTarget->GetFrame(), ImVec2(m_ViewportSize.x, m_ViewportSize.y));
		
		ImGui::End();
	}
}
