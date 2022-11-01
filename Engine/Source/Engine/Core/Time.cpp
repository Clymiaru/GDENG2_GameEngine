#include "pch.h"
#include "Time.h"

Engine::Time::Time() :
	m_DeltaTime{0.0},
	m_StartFrameTime{},
	m_EndFrameTime{}
{
}

Engine::Time::~Time() = default;

double Engine::Time::DeltaTime() const
{
	return m_DeltaTime;
}

auto Engine::Time::Start() -> void
{
	using namespace std::chrono;
	m_StartFrameTime = steady_clock::now();
}

auto Engine::Time::End() -> void
{
	using namespace std::chrono;
	
	m_EndFrameTime = steady_clock::now();

	const auto elapsed = m_EndFrameTime - m_StartFrameTime;

	const auto duration = duration_cast<milliseconds>(elapsed).count();
	
	m_DeltaTime = static_cast<double>(duration) / 1000.0;
}
