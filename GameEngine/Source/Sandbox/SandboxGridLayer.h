#pragma once
#include "Engine/Core/Layer.h"

namespace Sandbox
{
	class SandboxGridLayer : public Engine::Layer
	{
	public:
		SandboxGridLayer();

		~SandboxGridLayer() override;

		auto OnAttach() -> void override;

		auto OnUpdate() -> void override;

		auto OnRender() -> void override;

		auto OnDetach() -> void override;
	};
}
