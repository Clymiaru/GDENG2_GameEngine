#include "pch.h"
#include "Time.h"

namespace Engine
{
	Timer::Timer() :
		m_DeltaTimeMilliseconds{0.0},
		m_DeltaTimeSeconds{0.0f},
		m_StartFrameTime{},
		m_EndFrameTime{} { }

	Timer::~Timer() = default;

	void Timer::Start()
	{
		using namespace std::chrono;
		m_StartFrameTime = steady_clock::now();
	}

	void Timer::Stop()
	{
		using namespace std::chrono;

		m_EndFrameTime = steady_clock::now();

		const auto elapsed = m_EndFrameTime - m_StartFrameTime;

		const auto duration = duration_cast<milliseconds>(elapsed).count();

		m_DeltaTimeMilliseconds = (double)duration;
		m_DeltaTimeSeconds      = (float)duration / 1000.0f;
	}
	
	TimeData Timer::GetInfo() const
	{
		return TimeData{m_DeltaTimeSeconds,
		                m_DeltaTimeMilliseconds};
	}
}
