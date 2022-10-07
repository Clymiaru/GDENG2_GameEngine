#pragma once
#include <memory>

namespace Engine
{
	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateUniquePtr(Args&& ... args) -> UniquePtr<T>
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr auto CreateSharedPtr(Args&& ... args) -> SharedPtr<T>
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
