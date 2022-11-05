#pragma once
#include <DirectXMath.h>

#include "Vector2.h"

#include "Vector3.h"

#include "Matrix4.h"

#include "Color.h"

#include "Rect.h"

namespace Engine
{
	constexpr float DegreesToRadians(const float degrees)
	{
		using namespace DirectX;
		return XMConvertToRadians(degrees);
	}

	constexpr float RadiansToDegrees(const float radians)
	{
		using namespace DirectX;
		return XMConvertToDegrees(radians);
	}
}

// struct Vector4 (TODO);
// struct Quaternion (TODO);
// struct Ray (TODO);
// struct Viewport (TODO);
