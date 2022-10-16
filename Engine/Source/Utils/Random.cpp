#include "pch.h"
#include "Random.h"

Engine::Random::Random() :
	m_RandomEngine{}
{
}

Engine::Random& Engine::Random::Instance()
{
	static Random instance;
	return instance;
}
