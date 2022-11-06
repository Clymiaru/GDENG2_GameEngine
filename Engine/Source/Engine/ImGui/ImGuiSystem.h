#pragma once
#include <Windows.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"

#include <d3d11.h>

namespace Engine
{
	class Window;

	class ImGuiSystem
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

	private:
		static ImGuiContext* s_Context;

		static bool s_ShowDemoWindow;
	};
}
