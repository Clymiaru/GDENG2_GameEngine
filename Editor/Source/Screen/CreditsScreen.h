#pragma once

#include "Engine/UI/AUIPanel.h"

namespace Editor
{
	class CreditsScreen final : public Engine::AUIPanel
	{
	public:
		CreditsScreen();
		~CreditsScreen() override;

		void DrawImpl() override;
	};
}
