#pragma once
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class ViewportScreen final : Engine::AUIScreen
	{
	public:
		explicit ViewportScreen(Engine::ScreenID id);
		~ViewportScreen() override;

		ViewportScreen(const ViewportScreen&)                = delete;
		ViewportScreen& operator=(const ViewportScreen&)     = delete;
		ViewportScreen(ViewportScreen&&) noexcept            = delete;
		ViewportScreen& operator=(ViewportScreen&&) noexcept = delete;
	private:
		void DrawImpl() override;
	};
}
