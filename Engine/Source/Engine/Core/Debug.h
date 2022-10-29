#pragma once
#include <format>
#include <iostream>

namespace Engine
{
	class Debug
	{
	public:
		template <typename... Args>
		static void Log(std::wstring_view message,
		                Args&&... args);
	};

	template <typename... Args>
	void Debug::Log(const std::wstring_view message,
	                Args&&... args)
	{
#ifdef DEBUG
		std::wcout << std::vformat(message, std::make_wformat_args(args...)) << "\n";
#endif
	}

#define STRINGIFY(x) #x
#define TO_STRING(x) (STRINGIFY(x))

// #if DEBUG
// #define ENGINE_ASSERT_TRUE(successCondition, ...) { if (!(successCondition))\
// 												    {\
// 														Debug::Log(L"Assertion: {0} ({1} @ Line:{2})", __VA_ARGS__, __FILE__, __LINE__);\
// 														__debugbreak(); \
// 													} }
// #else
#define ENGINE_ASSERT_TRUE(successCondition, errorMsg) { if (!(successCondition)) { } }
//#endif
}
