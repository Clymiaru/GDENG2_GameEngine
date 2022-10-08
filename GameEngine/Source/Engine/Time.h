#pragma once
#include <chrono>

namespace Engine
{
	class Time final
	{
	public:
		static void Initialize();

		static void Terminate();

		static double GetDeltaTime();

	private:
		Time();

		~Time();

		Time(const Time&) = delete;

		static Time* m_Instance;

		double m_DeltaTime;

		std::chrono::steady_clock::time_point m_StartFrameTime;

		std::chrono::steady_clock::time_point m_EndFrameTime;

		static void LogFrameStart();

		static void LogFrameEnd();

		friend class Window;
	};
}
