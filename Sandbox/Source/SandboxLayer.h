#pragma once
#include "Engine/Engine.h"

namespace Engine
{
	class Quad;
	class Cube;
}

namespace Sandbox
{
	class SandboxLayer final : public Engine::Layer
	{
	public:
		SandboxLayer();

		~SandboxLayer() override;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnDetach() override;

	private:
		float m_CurrentTime;
		float m_MaxTime;

		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Tiles;

		Engine::List< Engine::UniquePtr<Engine::Cube>> m_Cubes;

		Engine::UniquePtr<Engine::Cube> m_TestCube;

		float m_TestPosition[3] = {0.0f, 0.0f, 0.0f};
		float m_TestRotation[3] = {0.0f, 0.0f, 0.0f};
	};
}
