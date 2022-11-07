#pragma once



#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Engine
{
	using String = std::string;

	using StringView = std::string_view;
	
	template <typename T>
	using List = std::vector<T>;

	template <typename Key, typename Value>
	using HashMap = std::unordered_map<Key, Value>;

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