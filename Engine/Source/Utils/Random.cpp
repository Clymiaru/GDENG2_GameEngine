#include "pch.h"
#include "Random.h"

Engine::Random::Random() :
	m_RandomEngine{time(0)}
{
}

Engine::Random& Engine::Random::Instance()
{
	static Random instance;
	return instance;
}
