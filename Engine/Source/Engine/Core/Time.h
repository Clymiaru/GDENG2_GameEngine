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

	private:
		Time(const Time&) = delete;

		double m_DeltaTime;

		std::chrono::steady_clock::time_point m_StartFrameTime;

		std::chrono::steady_clock::time_point m_EndFrameTime;
	};
}
