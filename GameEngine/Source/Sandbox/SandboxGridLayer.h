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

		auto OnAttach() -> void override;

		auto OnUpdate() -> void override;

		auto OnRender() -> void override;

		auto OnDetach() -> void override;

	private:
		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Tiles;

		int m_Frames = 0;
		float m_ElapsedTime = 0.0f;
	};
}
