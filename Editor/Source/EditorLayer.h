#pragma once
#include <Engine/Core/Layer.h>

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

		void OnDetach() override;

		EditorLayer(const EditorLayer&) = delete;
		EditorLayer& operator=(const EditorLayer&) = delete;
		EditorLayer(EditorLayer&&) noexcept = delete;
		EditorLayer& operator=(EditorLayer&&) noexcept = delete;

	private:
		// Only support 1 Game View and 1 Editor View for now
		// Engine::UniquePtr<Engine::Framebuffer> m_EditorViewFramebuffer;
		//
		// Engine::UniquePtr<Engine::Framebuffer> m_GameViewFramebuffer;
	};
}
