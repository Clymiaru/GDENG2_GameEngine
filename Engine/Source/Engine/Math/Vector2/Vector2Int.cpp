#include "pch.h"
#include "Vector2Int.h"

namespace Engine
{
	Vector2Int Vector2Int::Zero = Vector2Int(0, 0);
	Vector2Int Vector2Int::One  = Vector2Int(1, 1);

	Vector2Int::Vector2Int() :
		XMINT2{0, 0} { }

	Vector2Int::Vector2Int(const int32_t x, const int32_t y) :
		XMINT2{x, y} { }

	Vector2Int::Vector2Int(const XMINT2& v) :
		XMINT2{v} { }

	Vector2Int::~Vector2Int() = default;

	float Vector2Int::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR result = XMVector2Length(v1);
		return XMVectorGetX(result);
	}

	float Vector2Int::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR result = XMVector2LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector2Int::Dot(const Vector2Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR v2     = XMLoadSInt2(&v);
		const XMVECTOR result = XMVector2Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector2Int Vector2Int::Cross(const Vector2Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadSInt2(this);
		const XMVECTOR v2         = XMLoadSInt2(&v);
		const XMVECTOR tempResult = XMVector2Cross(v1, v2);

		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	void Vector2Int::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR result = XMVector2Normalize(v1);
		XMStoreSInt2(this, result);
	}

	float Vector2Int::Distance(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt2(&v1);
		const XMVECTOR x2     = XMLoadSInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Int::DistanceSquared(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt2(&v1);
		const XMVECTOR x2     = XMLoadSInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Int Vector2Int::Min(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt2(&v1);
		const XMVECTOR x2  = XMLoadSInt2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Int result;
		XMStoreSInt2(&result, min);
		return result;
	}

	Vector2Int Vector2Int::Max(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt2(&v1);
		const XMVECTOR x2  = XMLoadSInt2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Int result;
		XMStoreSInt2(&result, max);
		return result;
	}

	Vector2Int Vector2Int::Lerp(const Vector2Int& v1, const Vector2Int& v2, const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadSInt2(&v1);
		const XMVECTOR x2         = XMLoadSInt2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Int result;
		XMStoreSInt2(&result, lerpVector);
		return result;
	}

	Vector2Int::operator DirectX::XMVECTOR() const
	{
		return XMLoadSInt2(this);
	}

	Vector2Int::operator int32_t*() const
	{
		return (int32_t*)this;
	}

	bool Vector2Int::operator==(const Vector2Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadSInt2(this);
		const XMVECTOR v2 = XMLoadSInt2(&v);
		return XMVector2Equal(v1, v2);
	}

	bool Vector2Int::operator!=(const Vector2Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadSInt2(this);
		const XMVECTOR v2 = XMLoadSInt2(&v);
		return XMVector2NotEqual(v1, v2);
	}

	Vector2Int& Vector2Int::operator+=(const Vector2Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR v2     = XMLoadSInt2(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreSInt2(this, result);
		return *this;
	}

	Vector2Int& Vector2Int::operator-=(const Vector2Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR v2     = XMLoadSInt2(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreSInt2(this, result);
		return *this;
	}

	Vector2Int& Vector2Int::operator*=(const Vector2Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR v2     = XMLoadSInt2(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreSInt2(this, result);
		return *this;
	}

	Vector2Int& Vector2Int::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreSInt2(this, result);
		return *this;
	}

	Vector2Int& Vector2Int::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadSInt2(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreSInt2(this, result);
		return *this;
	}

	Vector2Int Vector2Int::operator+() const
	{
		return *this;
	}

	Vector2Int Vector2Int::operator-() const
	{
		return Vector2Int(-x, -y);
	}

	Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator*(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator*(const Vector2Int& v, const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator/(const Vector2Int& v1, const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator/(const Vector2Int& v, const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadSInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Vector2Int& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << "}";
	// 	return os;
	// }
}
