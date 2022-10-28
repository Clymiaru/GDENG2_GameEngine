#pragma once

#include <windef.h>

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

		explicit Rect(const RECT& rect) :
			X((T)rect.left),
			Y((T)rect.top),
			Width((T)(rect.right - rect.left)),
			Height((T)(rect.bottom - rect.top))
		{
		}

		Rect(const Rect&) = default;
		Rect& operator=(const Rect&) = default;

		Rect(Rect&&) = default;
		Rect& operator=(Rect&&) = default;
	};
}
