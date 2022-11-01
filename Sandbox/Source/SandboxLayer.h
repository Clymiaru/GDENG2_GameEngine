#pragma once

#include <Engine/Core/Layer.h>

#include "Engine/Engine.h"
#include "Engine/SceneManagement/EditorSceneCameraHandler.h"

namespace Engine
{
	class Plane;
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
		// TODO: How to make this into only one list?
		Engine::List<Engine::Cube*> m_EntityList;
		Engine::Plane* m_Plane;
		
		Engine::EditorSceneCameraHandler m_CameraHandler;

		int m_CurrentSceneCamera = 0;
		bool m_IsDemoWindowOpen = false;

		int m_Frame = 0;
		float m_Timer = 0.0f;
		float m_Fps = 0.0f;
	};
}
