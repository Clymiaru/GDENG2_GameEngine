#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{
	class AUIHUD
	{
	public:
		explicit AUIHUD(const String& name);
		virtual ~AUIHUD() = default;

		void Draw();
	private:
		
		virtual void DrawImpl() = 0;

		String m_Name;
	};
}
