#include "pch.h"
#include "Vector2Float.h"

namespace Engine
{
	Vector2Float Vector2Float::Zero = Vector2Float(0.0f, 0.0f);
	Vector2Float Vector2Float::One  = Vector2Float(1.0f, 1.0f);

	Vector2Float::Vector2Float() :
		XMFLOAT2{0.0f, 0.0f} { }

	Vector2Float::Vector2Float(const float x, const float y) :
		XMFLOAT2{x, y} { }

	Vector2Float::Vector2Float(const DirectX::XMFLOAT2& v) :
		XMFLOAT2{v} { }

	Vector2Float::~Vector2Float() = default;

	float Vector2Float::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR result = XMVector2Length(v1);
		return XMVectorGetX(result);
	}

	float Vector2Float::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR result = XMVector2LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector2Float::Dot(const Vector2Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR v2     = XMLoadFloat2(&v);
		const XMVECTOR result = XMVector2Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector2Float Vector2Float::Cross(const Vector2Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadFloat2(this);
		const XMVECTOR v2         = XMLoadFloat2(&v);
		const XMVECTOR tempResult = XMVector2Cross(v1, v2);

		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	void Vector2Float::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR result = XMVector2Normalize(v1);
		XMStoreFloat2(this, result);
	}

	float Vector2Float::Distance(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat2(&v1);
		const XMVECTOR x2     = XMLoadFloat2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Float::DistanceSquared(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat2(&v1);
		const XMVECTOR x2     = XMLoadFloat2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Float Vector2Float::Min(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat2(&v1);
		const XMVECTOR x2  = XMLoadFloat2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Float result;
		XMStoreFloat2(&result, min);
		return result;
	}

	Vector2Float Vector2Float::Max(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat2(&v1);
		const XMVECTOR x2  = XMLoadFloat2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Float result;
		XMStoreFloat2(&result, max);
		return result;
	}

	Vector2Float Vector2Float::Lerp(const Vector2Float& v1, const Vector2Float& v2, const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadFloat2(&v1);
		const XMVECTOR x2         = XMLoadFloat2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Float result;
		XMStoreFloat2(&result, lerpVector);
		return result;
	}

	Vector2Float::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat2(this);
	}

	Vector2Float::operator float*() const
	{
		return (float*)this;
	}

	bool Vector2Float::operator==(const Vector2Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat2(this);
		const XMVECTOR v2 = XMLoadFloat2(&v);
		return XMVector2Equal(v1, v2);
	}

	bool Vector2Float::operator!=(const Vector2Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat2(this);
		const XMVECTOR v2 = XMLoadFloat2(&v);
		return XMVector2NotEqual(v1, v2);
	}

	Vector2Float& Vector2Float::operator+=(const Vector2Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR v2     = XMLoadFloat2(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreFloat2(this, result);
		return *this;
	}

	Vector2Float& Vector2Float::operator-=(const Vector2Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR v2     = XMLoadFloat2(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreFloat2(this, result);
		return *this;
	}

	Vector2Float& Vector2Float::operator*=(const Vector2Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR v2     = XMLoadFloat2(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreFloat2(this, result);
		return *this;
	}

	Vector2Float& Vector2Float::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreFloat2(this, result);
		return *this;
	}

	Vector2Float& Vector2Float::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadFloat2(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreFloat2(this, result);
		return *this;
	}

	Vector2Float Vector2Float::operator+() const
	{
		return *this;
	}

	Vector2Float Vector2Float::operator-() const
	{
		return Vector2Float(-x, -y);
	}

	Vector2Float operator+(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator-(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator*(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator*(const Vector2Float& v, const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator/(const Vector2Float& v1, const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator/(const Vector2Float& v, const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadFloat2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Vector2Float& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << "}";
	// 	return os;
	// }
}