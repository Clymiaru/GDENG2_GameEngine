#pragma once
#include "AUIScreen.h"

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

		static void Register(AUIScreen* uiScreen);
		static void Deregister(AUIScreen* uiScreen);
	private:
		// List of UI Screens
		// Issue: Draw UI Screen specific to scene?

		static List<AUIScreen*> s_UIScreenList;
	};
}
