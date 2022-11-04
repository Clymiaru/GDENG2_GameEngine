#pragma once
#include <Engine/Core/Layer.h>
#include <Engine/Engine.h>
#include <Engine/Graphics/Framebuffer.h>
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

		Engine::List<Engine::Framebuffer*> m_ViewportFramebuffers;

		// TODO: How to make this into only one list?
		Engine::List<Engine::Cube*> m_EntityList;
		Engine::Plane* m_Plane;
		
		Engine::EditorSceneCameraHandler m_CameraHandler;

		int m_CurrentSceneCamera = 0;
	};
}
