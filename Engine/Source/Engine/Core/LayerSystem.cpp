#include "pch.h"
#include "LayerSystem.h"

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

void Engine::LayerSystem::Update() const
{
	for (auto* layer : m_Layers)
	{
		layer->OnUpdate();
	}
}

void Engine::LayerSystem::Render() const
{
	for (auto* layer : m_Layers)
	{
		layer->OnRender();
	}
}
