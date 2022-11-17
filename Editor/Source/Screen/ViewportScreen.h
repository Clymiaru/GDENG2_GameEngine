#pragma once
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class ViewportScreen final : Engine::AUIScreen
	{
	public:
		explicit ViewportScreen(Engine::ScreenID id);
		~ViewportScreen() override;

	private:
		void DrawImpl() override;
	};

}
