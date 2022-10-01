#pragma once
#include "Engine/Application.h"

namespace Editor
{
	class EditorApplication final : public Engine::Application
	{
	public:
		explicit EditorApplication(Engine::Vector2Uint startWindowSize);

		~EditorApplication() override;

	private:
		auto InitializeSystems() -> void override;

		auto TerminateSystems() -> void override;
	};
}
