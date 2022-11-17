#include "pch.h"
#include "UISystem.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"
#include "Engine/Graphics/Renderer.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace Engine
{
	ImGuiContext* UISystem::s_Context = nullptr;

	bool UISystem::s_ShowDemoWindow = false;

	UIIDGenerator UISystem::s_ScreenIDGenerator = UIIDGenerator();

	HashMap<ScreenID, AUIScreen*> UISystem::s_UIScreenMap;
	
	List<AUIScreen*> UISystem::s_UIScreenList;

	UISystem::UISystem(Window& windowRef,
	                   Renderer& rendererRef)
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

		ImGui_ImplDX11_Init(rendererRef.GetDevice().m_Device,
		                    rendererRef.GetContext().m_DeviceContext);
	}

	UISystem::~UISystem()
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

	void UISystem::Destroy(const ScreenID screenID)
	{
		if (!s_UIScreenMap.contains(screenID))
			return;
		
		int index = -1;
		for (size_t i = 0; i < s_UIScreenList.size(); i++)
		{
			if (s_UIScreenList[i]->GetID() == screenID)
			{
				index = i;
			}
		}

		if (index == -1)
			return;

		auto* screenRef = s_UIScreenMap[screenID];

		s_ScreenIDGenerator.AddReservedUIID(screenID);

		auto screenIndex = std::ranges::remove(s_UIScreenList, screenRef);
		s_UIScreenList.erase(screenIndex.begin(), screenIndex.end());
		s_UIScreenList.shrink_to_fit();

		s_UIScreenMap.erase(screenID);

		delete screenRef;
	}
	
	void UISystem::DrawUI()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport();

		for (auto i = 0ULL; i < s_UIScreenList.size(); ++i)
		{
			s_UIScreenList[i]->Draw();
		}

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
		ImGuiIO& io = ImGui::GetIO();
	
		io.DisplaySize = ImVec2((float)Application::GetWindowInfo().Width,
		                        (float)Application::GetWindowInfo().Height);
	
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}
