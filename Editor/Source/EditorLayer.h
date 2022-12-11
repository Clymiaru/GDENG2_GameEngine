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

		void OnStart() override;

		void OnPollInput(const Engine::InputData& inputData) override;
		
		void OnUpdate(const Engine::TimeData& timeData) override;

		void OnRender() override;

		void OnDetach() override;

		EditorLayer(const EditorLayer&) = delete;
		EditorLayer& operator=(const EditorLayer&) = delete;
		EditorLayer(EditorLayer&&) noexcept = delete;
		EditorLayer& operator=(EditorLayer&&) noexcept = delete;

	private:
		int m_NumberOfEditorViewports = 1;		
	};
}
