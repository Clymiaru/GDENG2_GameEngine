#pragma once
#include <format>
#include <iostream>
#include <source_location>

namespace Engine::Debug
{
	template <typename... Args>
	void Log(const std::string_view message,
	         Args&&... args)
	{
#ifdef DEBUG
		std::cout << std::vformat(message, std::make_format_args(args...)) << "\n";
#endif
	}

	template <typename... Args>
	void Log(const std::wstring_view message,
	         Args&&... args)
	{
#ifdef DEBUG
		std::wcout << std::vformat(message, std::make_wformat_args(args...)) << "\n";
#endif
	}

	template <typename... Args>
	class Assert
	{
	public:
		Assert(bool successCondition,
		       const std::source_location& loc = std::source_location::current());

		Assert(bool successCondition,
		       std::string_view message,
		       Args&&... args,
		       const std::source_location& loc = std::source_location::current());
	};

	template <typename... Args>
	Assert<Args...>::Assert(bool successCondition,
	                        const std::source_location& loc)
	{
#ifdef DEBUG
		if (!successCondition)
		{
			Log("Assertion Failed | {0} @ ({1} Line: {2})",
			    loc.function_name(),
			    loc.file_name(),
			    loc.line());

			__debugbreak();
		}
#endif
	}

	template <typename... Args>
	Assert<Args...>::Assert(bool successCondition,
	                        const std::string_view message,
	                        Args&&... args,
	                        const std::source_location& loc)
	{
#ifdef DEBUG
		if (!successCondition)
		{
			Log("Assertion Failed: {0} | {1} @ ({2} Line: {3})",
			    std::vformat(message, std::make_format_args(args...)),
			    loc.function_name(),
			    loc.file_name(),
			    loc.line());

			__debugbreak();
		}
#endif
	}

	template <typename... Args>
	Assert(bool,
	       std::string_view,
	       Args&&...) -> Assert<Args...>;

#define STRINGIFY(x) #x
#define TO_STRING(x) (STRINGIFY(x))
//
// 	// #if DEBUG
// 	// #define ENGINE_ASSERT_TRUE(successCondition, ...) { if (!(successCondition))\
// 	// 												    {\
// 	// 														Debug::Log(L"Assertion: {0} ({1} @ Line:{2})", __VA_ARGS__, __FILE__, __LINE__);\
// 	// 														__debugbreak(); \
// 	// 													} }
// 	// #else
// #define ENGINE_ASSERT_TRUE(successCondition, errorMsg) { if (!(successCondition)) { } }
// 	//#endif
}
