#include "pch.h"
#include "UIHandler.h"

namespace Engine
{
	List<AUIScreen*> UIHandler::s_UIScreenList = List<AUIScreen*>();
	
	void UIHandler::Start()
	{
	}

	void UIHandler::End()
	{
	}

	void UIHandler::Register(AUIScreen* uiScreen)
	{
	}

	void UIHandler::Deregister(AUIScreen* uiScreen)
	{
	}
}
