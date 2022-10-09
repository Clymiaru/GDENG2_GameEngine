#include "pch.h"
#include "Layer.h"

Engine::Layer::Layer(const std::string& name) :
	m_Name{name}
{
}

Engine::Layer::~Layer() = default;

auto Engine::Layer::GetName() const -> const std::string&
{
	return m_Name;
}
