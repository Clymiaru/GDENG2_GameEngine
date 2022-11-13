#pragma once
#include "Layer.h"

namespace Engine
{
	class LayerHandler final
	{
	public:
		explicit LayerHandler(size_t expectedLayerCount = 5);

		~LayerHandler();

		void StartLayers();
		void EndLayers();
		
		void Add(Layer* layer);
		void Remove(Layer* layer);

		void PollInput() const;
		void Update() const;
		void Render() const;
		void ImGuiRender() const;
	private:
		List<Layer*> m_Layers{};
		List<Layer*> m_ActiveLayers{};
	};
}

