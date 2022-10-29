#pragma once
#include "Layer.h"

namespace Engine
{
	class LayerSystem final
	{
	public:
		explicit LayerSystem(size_t expectedLayerCount = 5);

		~LayerSystem();

		void Start() const;

		void End();
		
		void Add(Layer* layer);
		// void Remove(Layer* layer);

		void PollInput(InputHandler* inputHandlerRef) const;
		void Update() const;
		void Render(Renderer* rendererRef) const;
		void ImGuiRender() const;
	private:
		List<Layer*> m_Layers{};
	};
}

