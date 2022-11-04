#pragma once

#include "Engine/UI/AUIScreen.h"

namespace Editor
{
	class CreditsScreen final : public Engine::AUIScreen
	{
	public:
		CreditsScreen();
		~CreditsScreen() override;

		void Draw() override;
	};
}
