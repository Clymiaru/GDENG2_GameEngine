#include "pch.h"
#include "LayerHandler.h"

#include "Application.h"

#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

#include "Engine/Graphics/Renderer.h"

namespace Engine
{
	LayerHandler::LayerHandler(const size_t expectedLayerCount)
	{
		m_Layers.reserve(expectedLayerCount);
		m_ActiveLayers.reserve(expectedLayerCount);
	}

	LayerHandler::~LayerHandler()
	{
		m_ActiveLayers.clear();
		m_Layers.clear();
	}

	void LayerHandler::StartLayers()
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

	void LayerHandler::EndLayers()
	{
		for (auto i = 0L; i < (long)m_ActiveLayers.size(); i++)
		{
			m_ActiveLayers[i]->OnDetach();
			m_ActiveLayers.erase(m_ActiveLayers.begin(),
			                     m_ActiveLayers.begin() + i);
		}
	}

	void LayerHandler::Add(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerHandler::Remove(Layer* layer)
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

	void LayerHandler::PollInput() const
	{
		for (auto* layer : m_Layers)
		{
			layer->OnPollInput();
		}
	}

	void LayerHandler::Update() const
	{
		for (auto* layer : m_Layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerHandler::Render() const
	{
		for (auto* layer : m_Layers)
		{
			// TODO: Mght require refactor since checking for null may be more expensive than emptyFrame buffer;
			const Framebuffer* layerFramebuffer = layer->GetFramebuffer();
			if (layerFramebuffer == nullptr)
				continue;

			Renderer::StartRender(*layerFramebuffer);

			layer->OnRender();

			Renderer::EndRender(*layerFramebuffer);
		}
	}

	void LayerHandler::ImGuiRender() const
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (auto* layer : m_Layers)
		{
			layer->OnImGuiRender();
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

		ImGui::EndFrame();
	}
}
