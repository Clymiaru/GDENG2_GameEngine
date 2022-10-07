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
	m_Instance->m_StartFrameTime = std::chrono::system_clock::now();
}

void Engine::Time::LogFrameEnd()
{
	m_Instance->m_EndFrameTime = std::chrono::system_clock::now();
	const auto elapsedSeconds  = m_Instance->m_EndFrameTime - m_Instance->m_StartFrameTime;
	m_Instance->m_DeltaTime    = static_cast<double>(elapsedSeconds.count());
}
