#pragma once
#include <Engine/Core/Layer.h>
#include <Engine/SceneManagement/EditorSceneCameraHandler.h>

namespace Engine
{
	class PostProcessHandler;

	class RenderQuad;

	class PostProcessQuad;

	class Scene;

	class Plane;

	class Cube;

	class EditorSceneCamera;

	class Entity;

	struct KeyEvent;
}

namespace Editor
{
	class EntityPropertiesPanel;
	class WorldOutlinerPanel;
	class PostProcessingPanel;
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
		// Only support 1 Game View and 1 Editor View for now
		Engine::UniquePtr<Engine::Framebuffer> m_EditorViewFramebuffer;

		Engine::UniquePtr<Engine::Framebuffer> m_GameViewFramebuffer;

		Engine::List<Engine::Entity*> m_EntityList;

		Engine::EditorSceneCameraHandler m_CameraHandler;

		Engine::UniquePtr<Engine::RenderQuad> m_RenderQuad;

		Engine::UniquePtr<Engine::PostProcessHandler> m_PostProcessHandler;

		int m_ChromaticEffectID;

		int m_CurrentSceneCamera = 0;

		// For PostProcessing Effects Demo
		PostProcessingPanel* m_PostProcessingPanel = nullptr;
		WorldOutlinerPanel* m_WorldOutlinerPanel = nullptr;
		EntityPropertiesPanel* m_EntityPropertiesPanel = nullptr;
	};
}
