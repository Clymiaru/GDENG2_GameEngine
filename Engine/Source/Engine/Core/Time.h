#pragma once
#include <chrono>

namespace Engine
{
	class Time final
	{
	public:
		Time();

		~Time();

		void Start();

		void End();

		[[nodiscard]]
		double DeltaTime() const;

		Time(const Time&) = default;
	
		Time& operator=(const Time&) = default;
	
		Time(Time&&) noexcept = default;
	
		Time& operator=(Time&&) noexcept = default;
		
	private:
		double m_DeltaTime;

		std::chrono::steady_clock::time_point m_StartFrameTime;

		std::chrono::steady_clock::time_point m_EndFrameTime;
	};
}
