#include "pch.h"
#include "UIHandler.h"

namespace Engine
{
	List<AUIPanel*> UIHandler::s_UIScreenList = List<AUIPanel*>();
	
	void UIHandler::Start()
	{
	}

	void UIHandler::End()
	{
	}

	void UIHandler::Register(AUIPanel* uiScreen)
	{
	}

	void UIHandler::Deregister(AUIPanel* uiScreen)
	{
	}
}
