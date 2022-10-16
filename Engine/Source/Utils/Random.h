#pragma once
#include "Engine/Core/Math.h"

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

		std::mt19937 m_RandomEngine;
	};

	template <>
	inline int Random::Range(const int& min,
	                         const int& max)
	{
		const std::uniform_int_distribution distribution(min, max);
		return distribution(Instance().m_RandomEngine);
	}

	template <>
	inline float Random::Range(const float& min,
	                           const float& max)
	{
		const std::uniform_real_distribution distribution(min, max);
		return distribution(Instance().m_RandomEngine);
	}
}
