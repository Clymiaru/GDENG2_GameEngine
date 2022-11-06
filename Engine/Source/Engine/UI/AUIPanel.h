#pragma once
#include "Engine/Core/Core.h"
#include "../Dependencies/ImGui/imgui.h"

namespace Engine
{
	class AUIPanel
	{
	public:
		virtual ~AUIPanel() = default;
		explicit AUIPanel(const String& name);
		
		void Draw();
	private:
		
		virtual void DrawImpl() = 0;

		String m_Name;
	};
}
