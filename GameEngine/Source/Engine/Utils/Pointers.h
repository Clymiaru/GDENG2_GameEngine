#pragma once
#include <memory>

// Code Snippet Source: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
namespace Engine
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateScope(Args&& ... args) -> Scope<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateRef(Args&& ... args) -> Ref<T>
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
