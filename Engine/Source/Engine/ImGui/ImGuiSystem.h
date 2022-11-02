#pragma once

#include "../../Engine/Dependencies/ImGui/imgui.h"

namespace Engine
{
	class ImGuiSystem
	{
	public:
		static ImGuiSystem& Instance();

		void Start();

		void End();
		
	private:
		explicit ImGuiSystem();
		
		
		ImGuiContext* m_Context;  
	};
}
