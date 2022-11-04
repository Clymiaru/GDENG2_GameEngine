#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{
	class AUIScreen
	{
	public:
		virtual ~AUIScreen() = default;
		explicit AUIScreen(const String& name);
		
		void DrawImpl();
		
		virtual void Draw() = 0;
	private:
		String m_Name;
	};
}
