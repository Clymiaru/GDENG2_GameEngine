#pragma once

#include <Engine/Core/Layer.h>

#include "Engine/Engine.h"
#include "Engine/SceneManagement/EditorSceneCameraHandler.h"


namespace Engine
{
	class Cube;
	class EditorSceneCamera;
	class Entity;
	struct KeyEvent;
}

namespace Sandbox
{
	class SandboxLayer final : public Engine::Layer
	{
	public:
		SandboxLayer();

		~SandboxLayer() override;

		void OnAttach() override;

		void OnPollInput() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnImGuiRender() override;

		void OnDetach() override;

	private:
		Engine::List<Engine::Cube*> m_EntityList;
		Engine::EditorSceneCameraHandler m_CameraHandler;

		int m_CurrentSceneCamera = 0;
		bool m_IsDemoWindowOpen = true;

		int m_Frame = 0;
		float m_Timer = 0.0f;
		float m_Fps = 0.0f;
	};
}
