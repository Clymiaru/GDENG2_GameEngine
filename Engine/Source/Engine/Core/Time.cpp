#include "pch.h"
#include "Time.h"

Engine::Timer::Timer() :
	m_DeltaTime{0.0},
	m_StartFrameTime{},
	m_EndFrameTime{}
{
}

Engine::Timer::~Timer() = default;

double Engine::Timer::DeltaTime() const
{
	return m_DeltaTime;
}

auto Engine::Timer::Start() -> void
{
	using namespace std::chrono;
	m_StartFrameTime = steady_clock::now();
}

auto Engine::Timer::End() -> void
{
	using namespace std::chrono;
	
	m_EndFrameTime = steady_clock::now();

	const auto elapsed = m_EndFrameTime - m_StartFrameTime;

	const auto duration = duration_cast<milliseconds>(elapsed).count();
	
	m_DeltaTime = static_cast<double>(duration) / 1000.0;
}
