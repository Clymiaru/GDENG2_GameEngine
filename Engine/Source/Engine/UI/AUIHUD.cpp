#include "pch.h"
#include "AUIHUD.h"

namespace Engine
{
	AUIHUD::AUIHUD(const String& name) :
		m_Name{name}
	{
	}

	void AUIHUD::Draw()
	{
		DrawImpl();
	}
}

