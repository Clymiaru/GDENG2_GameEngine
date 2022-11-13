#include "pch.h"
#include "UISystem.h"

#include "Engine/Core/Window.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
															 UINT msg,
															 WPARAM wParam,
															 LPARAM lParam);

namespace Engine
{
	ImGuiContext* UISystem::s_Context = nullptr;

	bool UISystem::s_ShowDemoWindow = false;
	
	List<AUIScreen*> UISystem::s_UIScreenList = List<AUIScreen*>();

	void UISystem::Start(Window& windowRef, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		IMGUI_CHECKVERSION();
		s_Context = ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding              = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui::SetCurrentContext(s_Context);

		ImGui_ImplWin32_Init(windowRef.GetHandle());

		ImGui_ImplDX11_Init(device, deviceContext);
	}
	
	void UISystem::End()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void UISystem::ShowDemoWindow(const bool flag)
	{
		s_ShowDemoWindow = flag;
		ImGui::ShowDemoWindow(&s_ShowDemoWindow);
	}

	LRESULT UISystem::HandleEvents(const HWND windowHandle,
									  const UINT message,
									  const WPARAM wParam,
									  const LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(windowHandle, message, wParam, lParam);
	}

	void UISystem::Register(AUIScreen* uiScreen) { }

	void UISystem::Deregister(AUIScreen* uiScreen) { }
}
