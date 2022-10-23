#pragma once
#include <Engine/Graphics/RenderObjects/Plane.h>

#include "Engine/Engine.h"

#include "Engine/Input/InputSystem.h"

namespace Engine
{
	class Quad;

	class Cube;
}

namespace Sandbox
{
	class SandboxLayer final : public Engine::Layer,
	                           public Engine::IInputListener
	{
	public:
		SandboxLayer();

		~SandboxLayer() override;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnDetach() override;

		void OnKeyDown(int keyCode) override;

		void OnKeyUp(int keyCode) override;

	private:
		float m_CurrentTime;

		float m_MaxTime;

		Engine::UniquePtr<Engine::Cube> m_TestCube;

		Engine::UniquePtr<Engine::Plane> m_Plane;

		float m_TestPosition[3] = {0.0f, 0.0f, 0.0f};

		float m_TestScale[3] = {500.0f, 500.0f, 500.0f};

		float m_TestRotation[3] = {0.0f, 0.0f, 0.0f};

		float m_TestPosition2[3] = {0.0f, 0.0f, 0.0f};

		float m_TestScale2[3] = {100.0f, 100.0f, 100.0f};

		float m_TestRotation2[3] = {0.0f, 0.0f, 0.0f};
	};
}
