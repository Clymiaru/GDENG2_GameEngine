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

		void OnMouseMove(const Engine::Vector2& deltaMousePosition) override;

		void OnLeftMouseButtonDown(const Engine::Vector2& mousePosition) override;

		void OnLeftMouseButtonUp(const Engine::Vector2& mousePosition) override;

		void OnRightMouseButtonDown(const Engine::Vector2& mousePosition) override;

		void OnRightMouseButtonUp(const Engine::Vector2& mousePosition) override;

	private:
		float m_CurrentTime;

		float m_MaxTime;

		Engine::UniquePtr<Engine::Cube> m_TestCube;

		Engine::UniquePtr<Engine::Plane> m_Plane;

		float m_TestPosition[3] = {0.0f, 0.0f, 0.0f};

		float m_TestScale[3] = {100.0f, 100.0f, 100.0f};

		float m_TestRotation[3] = {0.0f, 0.0f, 0.0f};

		float m_TestPosition2[3] = {0.0f, 0.0f, 0.0f};

		float m_TestScale2[3] = {10.0f, 10.0f, 10.0f};

		float m_TestRotation2[3] = {0.0f, 0.0f, 0.0f};

		float m_CameraPosition[3] = {0.0f, 0.0f, 0.0f};
	};
}
