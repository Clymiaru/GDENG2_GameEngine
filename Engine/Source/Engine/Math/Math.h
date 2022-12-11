#pragma once
#include <DirectXMath.h>

//--------------------------------//
// Vector2                        //
//--------------------------------//
#include "Vector2/Vector2Float.h"
#include "Vector2/Vector2Int.h"
#include "Vector2/Vector2Uint.h"

//--------------------------------//
// Vector3                        //
//--------------------------------//
#include "Vector3/Vector3Float.h"
#include "Vector3/Vector3Int.h"
#include "Vector3/Vector3Uint.h"

// TODO
//--------------------------------//
// Vector4                        //
//--------------------------------//

// TODO
//--------------------------------//
// Quaternion                     //
//--------------------------------//
#include "Quaternion.h"

//--------------------------------//
// Matrix                         //
//--------------------------------//
#include "Matrix4.h"

//--------------------------------//
// Color                          //
//--------------------------------//
#include "Color.h"

//--------------------------------//
// Rect                           //
//--------------------------------//
#include "Rect.h"

// TODO
//--------------------------------//
// Ray                            //
//--------------------------------//

// TODO
//--------------------------------//
// Viewport                       //
//--------------------------------//

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

	constexpr float PI = 3.141592654f;
	constexpr float HALF_PI = 3.141592654f / 2.0f;
}
