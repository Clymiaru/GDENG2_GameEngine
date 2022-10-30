#pragma once

#include <Engine/Event/Event.h>

#include "Engine/Engine.h"

namespace Engine
{
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

		void OnPollInput(Engine::InputHandler* inputHandlerRef) override;

		void OnUpdate() override;

		void OnRender(Engine::Renderer* rendererRef) override;

		void OnImGuiRender() override;

		void OnDetach() override;

	private:
		Engine::List<Engine::Entity*> m_EntityList;

		Engine::MouseEvent* m_ActiveMouseEvent;
		Engine::KeyEvent* m_ActiveKeyEvent;

		bool m_IsDemoWindowOpen = true;
	};
}
