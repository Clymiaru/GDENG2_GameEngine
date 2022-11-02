#include "pch.h"
#include "Layer.h"

namespace Engine
{
	Layer::Layer(const String& name) :
		m_Name{name}
	{
	}

	Layer::~Layer() = default;

	const String& Layer::GetName() const
	{
		return m_Name;
	}
}
