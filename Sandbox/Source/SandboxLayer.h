#pragma once

#include <Engine/Core/Layer.h>

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

		void OnPollInput() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnImGuiRender() override;

		void OnDetach() override;

	private:
		Engine::List<Engine::Entity*> m_EntityList;

		bool m_IsDemoWindowOpen = true;
	};
}
