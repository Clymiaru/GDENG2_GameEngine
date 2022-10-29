#include "pch.h"
#include "LayerSystem.h"

#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

Engine::LayerSystem::LayerSystem(const size_t expectedLayerCount) :
	m_Layers{}
{
	m_Layers.reserve(expectedLayerCount);
}

Engine::LayerSystem::~LayerSystem() = default;

void Engine::LayerSystem::Start() const
{
	for (auto* layer : m_Layers)
	{
		layer->OnAttach();
	}
}

void Engine::LayerSystem::End()
{
	for (auto* layer : m_Layers)
	{
		layer->OnDetach();
	}
	m_Layers.clear();
}

void Engine::LayerSystem::Add(Layer* layer)
{
	m_Layers.emplace_back(layer);
}

void Engine::LayerSystem::PollInput(InputHandler* inputHandlerRef) const
{
	for (auto* layer : m_Layers)
	{
		layer->OnPollInput(inputHandlerRef);
	}
}

void Engine::LayerSystem::Update() const
{
	for (auto* layer : m_Layers)
	{
		layer->OnUpdate();
	}
}

void Engine::LayerSystem::Render(Renderer* rendererRef) const
{
	for (auto* layer : m_Layers)
	{
		layer->OnRender(rendererRef);
	}
}

void Engine::LayerSystem::ImGuiRender() const
{
	for (auto* layer : m_Layers)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		
		layer->OnImGuiRender();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		ImGui::EndFrame();
	}
}
