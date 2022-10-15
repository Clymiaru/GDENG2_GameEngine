#pragma once
#include <DirectXMath.h>

#include "Core.h"

namespace Engine
{
	template <typename T>
	struct Vector2
	{
		T X;

		T Y;
	};

	using Vector2Int = Vector2<Uint>;
	using Vector2Uint = Vector2<unsigned int>;
	using Vector2Float = Vector2<float>;

	template <typename T>
	struct Vector3
	{
		T X;

		T Y;

		T Z;
	};

	using Vector3Int = Vector3<Uint>;
	using Vector3Uint = Vector3<unsigned int>;
	using Vector3Float = Vector3<float>;

	template <typename T>
	struct Rect
	{
		T Top;

		T Left;

		T Bottom;

		T Right;

		T Width;

		T Height;

		Rect(T x,
		     T y,
		     T width,
		     T height) :
			Top{y},
			Left{x},
			Bottom{y + height},
			Right{x + width},
			Width{width},
			Height{height}
		{
		}
	};

	using RectUint = Rect<Uint>;
}