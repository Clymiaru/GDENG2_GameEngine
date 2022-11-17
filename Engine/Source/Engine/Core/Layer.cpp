#include "pch.h"
#include "Layer.h"

#include "Application.h"

namespace Engine
{
	Layer::Layer(const String& name) :
		m_Name{name}
	{
		
	}

	Layer::~Layer() = default;
}
