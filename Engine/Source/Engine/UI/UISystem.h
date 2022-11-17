#pragma once
#include <Windows.h>

#include "AUIScreen.h"

#include "../../Engine/Dependencies/ImGui/imgui.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

#include "Utils/UIIDGenerator.h"

namespace Engine
{
	class Window;
	class Renderer;

	// Issue is that Drawing of UI should happen on a separate layer
	
	// This UI is mainly for the editor
	class UISystem final
	{
	public:
		UISystem(Window& windowRef,
		         Renderer& rendererRef);
		~UISystem();

		static void ShowDemoWindow(bool flag);

		static LRESULT HandleEvents(HWND windowHandle,
		                            UINT message,
		                            WPARAM wParam,
		                            LPARAM lParam);

		template <typename UIScreen, typename... Args>
		static UIScreen* Create(Args&&... args);

		static void Destroy(ScreenID screenID);

		static void DrawUI();

	private:
		static ImGuiContext* s_Context;

		static bool s_ShowDemoWindow;

		static UIIDGenerator s_ScreenIDGenerator;
		
		static HashMap<ScreenID, AUIScreen*> s_UIScreenMap;
		static List<AUIScreen*> s_UIScreenList;
	};
	
	template <typename UIScreen, typename ... Args>
	UIScreen* UISystem::Create(Args&&... args)
	{
		ScreenID newID = s_ScreenIDGenerator.GenerateUIID();
		UIScreen* newScreen = new UIScreen(newID, std::forward<Args>(args)...);
		s_UIScreenList.push_back((AUIScreen*)newScreen);
		s_UIScreenMap[newID] = (AUIScreen*)newScreen;
		return newScreen;
	}
}
