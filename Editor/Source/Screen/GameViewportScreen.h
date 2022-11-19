#pragma once
#include <Engine/Math/Math.h>
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class GameViewportScreen final : Engine::AUIScreen
	{
	public:
		explicit GameViewportScreen(Engine::ScreenID id);
		~GameViewportScreen() override;

		GameViewportScreen(const GameViewportScreen&)                = delete;
		GameViewportScreen& operator=(const GameViewportScreen&)     = delete;
		GameViewportScreen(GameViewportScreen&&) noexcept            = delete;
		GameViewportScreen& operator=(GameViewportScreen&&) noexcept = delete;

	private:
		void DrawImpl() override;
		Engine::Vector2Uint m_ViewportSize;
	};
}
