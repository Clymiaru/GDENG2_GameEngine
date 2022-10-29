#include "pch.h"
#include "Layer.h"

Engine::Layer::Layer(const String& name) :
	m_Name{name}
{
}

Engine::Layer::~Layer() = default;

const Engine::String& Engine::Layer::GetName() const
{
	return m_Name;
}
