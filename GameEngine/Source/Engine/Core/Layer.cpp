#include "pch.h"
#include "Layer.h"

Engine::Layer::Layer(const std::string& name) :
	m_Name{name}
{
}

Engine::Layer::~Layer() = default;

const std::string& Engine::Layer::GetName() const
{
	return m_Name;
}
