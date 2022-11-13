#pragma once
#include <chrono>

namespace Engine
{
	struct TimeData
	{
		float DeltaTimeSec = 0.0f;
		double DeltaTimeMilli = 0.0;
		// TODO: Implement FixedDeltaTime;
	};
	
	class Timer final
	{
	public:
		Timer();

		~Timer();

		void Start();

		void End();

		[[nodiscard]]
		double DeltaTime() const;

		Timer(const Timer&) = default;
	
		Timer& operator=(const Timer&) = default;
	
		Timer(Timer&&) noexcept = default;
	
		Timer& operator=(Timer&&) noexcept = default;
		
	private:
		double m_DeltaTime;

		std::chrono::steady_clock::time_point m_StartFrameTime;

		std::chrono::steady_clock::time_point m_EndFrameTime;
	};
}
