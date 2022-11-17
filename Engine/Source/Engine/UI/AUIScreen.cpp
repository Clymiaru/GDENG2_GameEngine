#include "pch.h"
#include "AUIScreen.h"

namespace Engine
{
	AUIScreen::AUIScreen(ScreenID id, StringView name) :
		m_ID{id},
		m_Name{name.data()},
		m_NameIDLabel{std::vformat("{0}##{1}", std::make_format_args(name, id))},
		m_IsOpen{true}
	{}

	ScreenID AUIScreen::GetID() const
	{
		return m_ID;
	}
	
	const char* AUIScreen::GetNameAndIDLabel() const
	{
		return m_NameIDLabel.c_str();
	}

	void AUIScreen::Draw()
	{
		DrawImpl();
	}
}
