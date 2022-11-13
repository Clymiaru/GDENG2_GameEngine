#pragma once
#include "AUIPanel.h"

namespace Engine
{
	class UIHandler
	{
	public:
		static void Start();

		static void End();

		static void Register(AUIPanel* uiScreen);
		static void Deregister(AUIPanel* uiScreen);
	private:
		// List of UI Screens
		// Issue: Draw UI Screen specific to scene?

		static List<AUIPanel*> s_UIScreenList;
	};
}
