#pragma once
#include <random>

namespace Engine
{
	class Random final
	{
	public:
		template <typename T>
		static T Range(const T& min,
		               const T& max);

	private:
		Random();

		static Random& Instance();

		std::mt19937 m_RandomEngine{};
	};

	template <>
	inline int Random::Range(const int& min,
	                         const int& max)
	{
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(Instance().m_RandomEngine);
	}

	template <>
	inline float Random::Range(const float& min,
	                           const float& max)
	{
		std::uniform_real_distribution<float> distribution(min, max + 1.0f);
		return distribution(Instance().m_RandomEngine);
	}
}
