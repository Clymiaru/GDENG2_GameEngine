#pragma once
#include "Engine/Core/Layer.h"
#include "Engine/Utils/DataStructures.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class Quad;
}

namespace Sandbox
{
	class SandboxGridLayer final : public Engine::Layer
	{
	public:
		SandboxGridLayer();

		~SandboxGridLayer() override;

		void OnAttach() override;

		void OnUpdate() override;

		void OnRender() override;

		void OnDetach() override;

	private:
		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Tiles;
	};
}
