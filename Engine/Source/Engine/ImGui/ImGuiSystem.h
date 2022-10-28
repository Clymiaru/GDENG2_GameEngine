#pragma once

//Can't think of an appropriate name yet.
// Idea is that most if not all ImGui specific functionalities
// will be called using this class

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
