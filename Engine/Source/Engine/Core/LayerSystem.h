#pragma once
#include "Layer.h"
#include "Time.h"

#include "Engine/Input/InputData.h"
namespace Engine
{
	class LayerSystem final
	{
	public:
		explicit LayerSystem(size_t expectedLayerCount = 5);

		~LayerSystem();

		void StartLayers();
		void EndLayers();
		
		void Add(Layer* layer);
		// TODO: Add overlay layers?
		void Remove(Layer* layer);

		void PollInput(const InputData& inputData) const;
		void Update(const TimeData& timeData) const;
		void Render() const;

		LayerSystem(const LayerSystem&)                = delete;
		LayerSystem& operator=(const LayerSystem&)     = delete;
		LayerSystem(LayerSystem&&) noexcept            = delete;
		LayerSystem& operator=(LayerSystem&&) noexcept = delete;
	private:
		List<Layer*> m_Layers{};
		List<Layer*> m_ActiveLayers{};
	};
}

