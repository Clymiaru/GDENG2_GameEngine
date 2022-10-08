#include "pch.h"
#include "Time.h"

Engine::Time* Engine::Time::m_Instance = nullptr;

void Engine::Time::Initialize()
{
	m_Instance = new Time();
}

void Engine::Time::Terminate()
{
	delete m_Instance;
}

double Engine::Time::GetDeltaTime()
{
	return m_Instance->m_DeltaTime;
}

Engine::Time::Time() :
	m_DeltaTime{0.0},
	m_StartFrameTime{},
	m_EndFrameTime{}
{
}

Engine::Time::~Time()
{
}

void Engine::Time::LogFrameStart()
{
	using namespace std::chrono;
	m_Instance->m_StartFrameTime = steady_clock::now();
}

void Engine::Time::LogFrameEnd()
{
	using namespace std::chrono;
	using namespace std::chrono_literals;

	m_Instance->m_EndFrameTime = steady_clock::now();
	const auto elapsedSeconds  = m_Instance->m_EndFrameTime - m_Instance->m_StartFrameTime;

	m_Instance->m_DeltaTime = elapsedSeconds.count() / 100000000.0f;
}
