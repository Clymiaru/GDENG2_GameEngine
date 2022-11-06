#pragma once
#include "AUIPanel.h"

namespace Engine
{
	// Scene should have its own id.
	// Meaning that UI or game object for the scene

	// Another way is that we can have UI as a entity?
	// This way, we can just put in component?

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
