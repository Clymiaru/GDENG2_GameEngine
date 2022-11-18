#pragma once
#include <Engine/Core/Layer.h>

namespace Editor
{
	class EditorUILayer final : public Engine::Layer
	{
	public:
		explicit EditorUILayer();
		~EditorUILayer() override;
		void OnAttach() override;
		void OnPollInput() override;
		void OnUpdate() override;
		void OnRender() override;
		void OnDetach() override;

		EditorUILayer(const EditorUILayer&)                = delete;
		EditorUILayer& operator=(const EditorUILayer&)     = delete;
		EditorUILayer(EditorUILayer&&) noexcept            = delete;
		EditorUILayer& operator=(EditorUILayer&&) noexcept = delete;
	};

}
