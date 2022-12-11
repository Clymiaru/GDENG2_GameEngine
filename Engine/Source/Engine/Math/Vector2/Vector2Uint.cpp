#include "pch.h"
#include "Vector2Uint.h"

namespace Engine
{
	Vector2Uint Vector2Uint::Zero = Vector2Uint(0, 0);
	Vector2Uint Vector2Uint::One  = Vector2Uint(1, 1);

	Vector2Uint::Vector2Uint() :
		XMUINT2{0ULL, 0ULL} { }

	Vector2Uint::Vector2Uint(const uint32_t x, const uint32_t y) :
		XMUINT2{x, y} { }

	Vector2Uint::Vector2Uint(const XMUINT2& v) :
		XMUINT2{v} { }

	Vector2Uint::~Vector2Uint() = default;

	float Vector2Uint::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR result = XMVector2Length(v1);
		return XMVectorGetX(result);
	}

	float Vector2Uint::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR result = XMVector2LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector2Uint::Dot(const Vector2Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR v2     = XMLoadUInt2(&v);
		const XMVECTOR result = XMVector2Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector2Uint Vector2Uint::Cross(const Vector2Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadUInt2(this);
		const XMVECTOR v2         = XMLoadUInt2(&v);
		const XMVECTOR tempResult = XMVector2Cross(v1, v2);

		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	void Vector2Uint::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR result = XMVector2Normalize(v1);
		XMStoreUInt2(this, result);
	}

	float Vector2Uint::Distance(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt2(&v1);
		const XMVECTOR x2     = XMLoadUInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Uint::DistanceSquared(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt2(&v1);
		const XMVECTOR x2     = XMLoadUInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Uint Vector2Uint::Min(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt2(&v1);
		const XMVECTOR x2  = XMLoadUInt2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Uint result;
		XMStoreUInt2(&result, min);
		return result;
	}

	Vector2Uint Vector2Uint::Max(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt2(&v1);
		const XMVECTOR x2  = XMLoadUInt2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Uint result;
		XMStoreUInt2(&result, max);
		return result;
	}

	Vector2Uint Vector2Uint::Lerp(const Vector2Uint& v1, const Vector2Uint& v2, const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadUInt2(&v1);
		const XMVECTOR x2         = XMLoadUInt2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Uint result;
		XMStoreUInt2(&result, lerpVector);
		return result;
	}

	Vector2Uint::operator DirectX::XMVECTOR() const
	{
		return XMLoadUInt2(this);
	}

	Vector2Uint::operator uint32_t*() const
	{
		return (uint32_t*)this;
	}

	bool Vector2Uint::operator==(const Vector2Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadUInt2(this);
		const XMVECTOR v2 = XMLoadUInt2(&v);
		return XMVector2Equal(v1, v2);
	}

	bool Vector2Uint::operator!=(const Vector2Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadUInt2(this);
		const XMVECTOR v2 = XMLoadUInt2(&v);
		return XMVector2NotEqual(v1, v2);
	}

	Vector2Uint& Vector2Uint::operator+=(const Vector2Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR v2     = XMLoadUInt2(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreUInt2(this, result);
		return *this;
	}

	Vector2Uint& Vector2Uint::operator-=(const Vector2Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR v2     = XMLoadUInt2(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreUInt2(this, result);
		return *this;
	}

	Vector2Uint& Vector2Uint::operator*=(const Vector2Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR v2     = XMLoadUInt2(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreUInt2(this, result);
		return *this;
	}

	Vector2Uint& Vector2Uint::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreUInt2(this, result);
		return *this;
	}

	Vector2Uint& Vector2Uint::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadUInt2(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreUInt2(this, result);
		return *this;
	}

	Vector2Uint Vector2Uint::operator+() const
	{
		return *this;
	}

	Vector2Uint operator+(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator-(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator*(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator*(const Vector2Uint& v, const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator/(const Vector2Uint& v1, const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator/(const Vector2Uint& v, const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadUInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Vector2Uint& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << "}";
	// 	return os;
	// }
}