#pragma once

namespace Engine
{
	template <typename T>
	struct Rect
	{
		T X;

		T Y;

		T Width;

		T Height;

		explicit Rect()
		{
		}

		explicit Rect(T x,
		              T y,
		              T width,
		              T height) :
			X(x),
			Y(y),
			Width(width),
			Height(height)
		{
		}

		Rect(const Rect&) = default;
		Rect& operator=(const Rect&) = default;

		Rect(Rect&&) = default;
		Rect& operator=(Rect&&) = default;
	};
}
