#pragma once
#include <memory>

// Code Snippet Source: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Base.h
namespace Engine
{
	template <typename T>
	using ScopePtr = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateUniquePtr(Args&& ... args) -> ScopePtr<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateRef(Args&& ... args) -> SharedPtr<T>
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
