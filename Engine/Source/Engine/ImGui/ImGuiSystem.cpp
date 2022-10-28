#include "pch.h"
#include "ImGuiSystem.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

Engine::ImGuiSystem::ImGuiSystem() :
	m_Context{nullptr}
{
}

Engine::ImGuiSystem& Engine::ImGuiSystem::Instance()
{
	static ImGuiSystem instance;
	return instance;
}

void Engine::ImGuiSystem::Start()
{
	IMGUI_CHECKVERSION();
	m_Context = ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui::SetCurrentContext(m_Context);
}

void Engine::ImGuiSystem::End()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
