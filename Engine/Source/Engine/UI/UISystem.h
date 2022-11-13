#pragma once
#include <Windows.h>
#include <d3d11.h>

#include "AUIScreen.h"

#include "../../Engine/Dependencies/ImGui/imgui.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

namespace Engine
{
	class Window;

	class UISystem
	{
	public:
		static void Start(Window& windowRef,
							ID3D11Device* device,
							ID3D11DeviceContext* deviceContext);

		static void End();

		static void ShowDemoWindow(bool flag);

		static LRESULT HandleEvents(HWND windowHandle,
									UINT message,
									WPARAM wParam,
									LPARAM lParam);

		static void Register(AUIScreen* uiScreen);
		static void Deregister(AUIScreen* uiScreen);
		
	private:
		static ImGuiContext* s_Context;

		static bool s_ShowDemoWindow;
		
		// List of UI Screens
		// Issue: Draw UI Screen specific to scene?

		static List<AUIScreen*> s_UIScreenList;
	};
}
