#pragma once
#include <format>

namespace Engine
{
	class Debug
	{
	public:
		template <typename... Args>
		static void Log(StringView message,
		                Args&&... args);
	};

	template <typename ... Args>
	void Debug::Log(const StringView message,
	                Args&&... args)
	{
#ifdef DEBUG
		std::cerr << std::vformat(message, std::make_format_args(args...)) << "\n";
#endif
	}

#define STRINGIFY(x) #x
#define TO_STRING(x) (STRINGIFY(x))

#if DEBUG
#define ENGINE_ASSERT(successCondition, ...) { if (!(successCondition))\
												    {\
														Debug::Log("Assertion: {0} ({1} @ Line:{2})", __VA_ARGS__, __FILE__, __LINE__);\
														__debugbreak(); \
													} }
#else
#define ENGINE_ASSERT(successCondition, errorMsg) { if (!(successCondition)) { } }
#endif
}
