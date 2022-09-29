#pragma once
namespace Engine
{
	template <typename T>
	struct Vector2
	{
		T X;

		T Y;
	};

	using Vector2Int = Vector2<int>;
	using Vector2Uint = Vector2<unsigned int>;
	
	template <typename T>
	struct Vector3
	{
		T X;

		T Y;

		T Z;
	};

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
}
