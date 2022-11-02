#pragma once
#include <Engine/Engine.h>

namespace Engine
{
	class Scene;
}

namespace Editor
{
	class EditorLayer : public Engine::Layer
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

	private:
		Engine::Scene* m_ActiveScene;
	};
}

