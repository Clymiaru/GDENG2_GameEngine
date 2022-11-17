#include "pch.h"
#include "LayerSystem.h"

namespace Engine
{
	LayerSystem::LayerSystem(const size_t expectedLayerCount)
	{
		m_Layers.reserve(expectedLayerCount);
		m_ActiveLayers.reserve(expectedLayerCount);
	}

	LayerSystem::~LayerSystem()
	{
		m_ActiveLayers.clear();
		m_Layers.clear();
	}

	void LayerSystem::StartLayers()
	{
		for (auto* layer : m_Layers)
		{
			if (std::ranges::find(m_ActiveLayers, layer) != m_ActiveLayers.end())
			{
				continue;
			}

			layer->OnAttach();
			m_ActiveLayers.push_back(layer);
		}
	}

	void LayerSystem::EndLayers()
	{
		for (auto i = 0L; i < (long)m_ActiveLayers.size(); i++)
		{
			m_ActiveLayers[i]->OnDetach();
			m_ActiveLayers.erase(m_ActiveLayers.begin(),
			                     m_ActiveLayers.begin() + i);
		}
	}

	void LayerSystem::Add(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerSystem::Remove(Layer* layer)
	{
		const auto resultFromLayers = std::ranges::find(m_Layers, layer);

		if (resultFromLayers == m_Layers.end())
		{
			return;
		}

		if (const auto resultFromActiveLayers =
					std::ranges::find(m_ActiveLayers, *resultFromLayers);
			resultFromActiveLayers != m_ActiveLayers.end())
		{
			(*resultFromActiveLayers)->OnDetach();
			m_ActiveLayers.erase(m_ActiveLayers.begin(),
			                     resultFromActiveLayers);
		}

		m_Layers.erase(resultFromLayers);
	}

	void LayerSystem::PollInput() const
	{
		for (int i = (int)m_ActiveLayers.size() - 1; i >= 0; --i)
		{
			m_ActiveLayers[i]->OnPollInput();
		}
	}

	void LayerSystem::Update() const
	{
		for (auto* layer : m_Layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerSystem::Render() const
	{
		// In forward order
		for (size_t i = 0; i < m_ActiveLayers.size(); ++i)
		{
			m_ActiveLayers[i]->OnRender(); // Let each layer handle their own rendering
		}
	}

	// void LayerSystem::ImGuiRender() const
	// {
	// 	ImGui_ImplDX11_NewFrame();
	// 	ImGui_ImplWin32_NewFrame();
	// 	ImGui::NewFrame();
	//
	// 	for (auto* layer : m_Layers)
	// 	{
	// 		layer->OnImGuiRender();
	// 	}
	//
	// 	ImGui::Render();
	// 	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//
	// 	ImGuiIO& io = ImGui::GetIO();
	//
	// 	io.DisplaySize = ImVec2((float)Application::GetWindowInfo().Width,
	// 	                        (float)Application::GetWindowInfo().Height);
	//
	// 	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	// 	{
	// 		ImGui::UpdatePlatformWindows();
	// 		ImGui::RenderPlatformWindowsDefault();
	// 	}
	//
	// 	ImGui::EndFrame();
	// }
}
