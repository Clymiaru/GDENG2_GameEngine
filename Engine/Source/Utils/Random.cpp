#include "pch.h"
#include "Random.h"

namespace Engine
{
	std::mt19937 g_RandomEngine;

	Random::Random()
	{
		m_RandomEngine.seed(std::random_device()());
	}

	Random& Random::Instance()
	{
		static Random instance;
		return instance;
	}
}
