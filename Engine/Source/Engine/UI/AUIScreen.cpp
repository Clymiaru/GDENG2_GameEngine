#include "pch.h"
#include "AUIScreen.h"

namespace Engine
{
	AUIScreen::AUIScreen(const StringView name) :
		m_Name{name.data()} {}
	
	void AUIScreen::Draw()
	{
		DrawImpl();
	}
}
