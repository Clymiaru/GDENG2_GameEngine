#include "pch.h"
#include "Time.h"

Engine::Time Engine::Time::m_Instance = Time();

auto Engine::Time::Initialize() -> void
{
}

auto Engine::Time::Terminate() -> void
{
}

auto Engine::Time::GetDeltaTime() -> double
{
	return m_Instance.m_DeltaTime;
}

Engine::Time::Time() :
	m_DeltaTime{0.0},
	m_StartFrameTime{},
	m_EndFrameTime{}
{
}

Engine::Time::~Time() = default;

auto Engine::Time::LogFrameStart() -> void
{
	using namespace std::chrono;
	m_Instance.m_StartFrameTime = steady_clock::now();
}

auto Engine::Time::LogFrameEnd() -> void
{
	using namespace std::chrono;
	
	m_Instance.m_EndFrameTime = steady_clock::now();

	const auto elapsed = m_Instance.m_EndFrameTime - m_Instance.m_StartFrameTime;

	const auto duration = duration_cast<milliseconds>(elapsed).count();

	m_Instance.m_DeltaTime = static_cast<double>(duration);
}
