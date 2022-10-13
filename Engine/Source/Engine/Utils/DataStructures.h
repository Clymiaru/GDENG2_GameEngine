#pragma once

#include <unordered_map>
#include <vector>

namespace Engine
{
	template <typename T>
	using List = std::vector<T>;

	template <typename Key, typename Value>
	using HashMap = std::unordered_map<Key, Value>;
}
