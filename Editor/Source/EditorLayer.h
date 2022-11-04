#pragma once
#include <Engine/Core/Layer.h>
#include <Engine/Engine.h>
#include <Engine/Graphics/Framebuffer.h>
//#include <Engine/Graphics/PostProcessQuad.h>
#include <Engine/SceneManagement/EditorSceneCameraHandler.h>

#include "Screen/CreditsScreen.h"

namespace Engine
{
	class Scene;

	class Plane;

	class Cube;

	class EditorSceneCamera;

	class Entity;

	struct KeyEvent;
}

namespace Editor
{
	class EditorLayer final : public Engine::Layer
	{
	public:
		EditorLayer();

		~EditorLayer() override;

		void OnAttach() override;

		void OnPollInput() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnImGuiRender() override;

		void OnDetach() override;

		EditorLayer(const EditorLayer&) = delete;

		EditorLayer& operator=(const EditorLayer& v) = delete;

		EditorLayer(EditorLayer&&) noexcept = delete;

		EditorLayer& operator=(EditorLayer&&) noexcept = delete;

	private:
		CreditsScreen* m_CreditsScreen;

		// Only support 1 Game View and 1 Editor View for now
		Engine::Framebuffer* m_EditorViewFramebuffer;

		Engine::Framebuffer* m_GameViewFramebuffer;
		
		// TODO: How to make this into only one list?
		Engine::List<Engine::Cube*> m_EntityList;
		Engine::Plane* m_Plane;

		// Engine::PostProcessQuad* m_PostProcessQuad;
		
		Engine::EditorSceneCameraHandler m_CameraHandler;

		int m_CurrentSceneCamera = 0;
	};
}
