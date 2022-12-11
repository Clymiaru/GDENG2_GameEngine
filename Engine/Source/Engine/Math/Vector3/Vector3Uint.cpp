#include "pch.h"
#include "Vector3Uint.h"

namespace Engine
{
	Vector3Uint Vector3Uint::Zero = Vector3Uint(0, 0, 0);
	Vector3Uint Vector3Uint::One  = Vector3Uint(1, 1, 1);

	Vector3Uint::Vector3Uint() :
		XMUINT3{0ULL, 0ULL, 0LL} { }

	Vector3Uint::Vector3Uint(const uint32_t x, const uint32_t y, const uint32_t z) :
		XMUINT3{x, y, z} { }

	Vector3Uint::Vector3Uint(const XMUINT3& v) :
		XMUINT3{v} { }

	Vector3Uint::~Vector3Uint() = default;

	float Vector3Uint::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR result = XMVector3Length(v1);
		return XMVectorGetX(result);
	}

	float Vector3Uint::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR result = XMVector3LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector3Uint::Dot(const Vector3Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR v2     = XMLoadUInt3(&v);
		const XMVECTOR result = XMVector3Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector3Uint Vector3Uint::Cross(const Vector3Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadUInt3(this);
		const XMVECTOR v2         = XMLoadUInt3(&v);
		const XMVECTOR tempResult = XMVector3Cross(v1, v2);

		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	void Vector3Uint::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR result = XMVector3Normalize(v1);
		XMStoreUInt3(this, result);
	}

	float Vector3Uint::Distance(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt3(&v1);
		const XMVECTOR x2     = XMLoadUInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3Length(net);
		return XMVectorGetX(result);
	}

	float Vector3Uint::DistanceSquared(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt3(&v1);
		const XMVECTOR x2     = XMLoadUInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector3Uint Vector3Uint::Min(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt3(&v1);
		const XMVECTOR x2  = XMLoadUInt3(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector3Uint result;
		XMStoreUInt3(&result, min);
		return result;
	}

	Vector3Uint Vector3Uint::Max(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt3(&v1);
		const XMVECTOR x2  = XMLoadUInt3(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector3Uint result;
		XMStoreUInt3(&result, max);
		return result;
	}

	Vector3Uint Vector3Uint::Lerp(const Vector3Uint& v1, const Vector3Uint& v2, const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadUInt3(&v1);
		const XMVECTOR x2         = XMLoadUInt3(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector3Uint result;
		XMStoreUInt3(&result, lerpVector);
		return result;
	}

	Vector3Uint::operator DirectX::XMVECTOR() const
	{
		return XMLoadUInt3(this);
	}

	Vector3Uint::operator uint32_t*() const
	{
		return (uint32_t*)this;
	}

	bool Vector3Uint::operator==(const Vector3Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadUInt3(this);
		const XMVECTOR v2 = XMLoadUInt3(&v);
		return XMVector3Equal(v1, v2);
	}

	bool Vector3Uint::operator!=(const Vector3Uint& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadUInt3(this);
		const XMVECTOR v2 = XMLoadUInt3(&v);
		return XMVector3NotEqual(v1, v2);
	}

	Vector3Uint& Vector3Uint::operator+=(const Vector3Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR v2     = XMLoadUInt3(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreUInt3(this, result);
		return *this;
	}

	Vector3Uint& Vector3Uint::operator-=(const Vector3Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR v2     = XMLoadUInt3(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreUInt3(this, result);
		return *this;
	}

	Vector3Uint& Vector3Uint::operator*=(const Vector3Uint& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR v2     = XMLoadUInt3(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreUInt3(this, result);
		return *this;
	}

	Vector3Uint& Vector3Uint::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreUInt3(this, result);
		return *this;
	}

	Vector3Uint& Vector3Uint::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadUInt3(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreUInt3(this, result);
		return *this;
	}

	Vector3Uint Vector3Uint::operator+() const
	{
		return *this;
	}

	Vector3Uint operator+(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator-(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator*(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator*(const Vector3Uint& v, const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator/(const Vector3Uint& v1, const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator/(const Vector3Uint& v, const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadUInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Vector3Uint& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
	// 	return os;
	// }
}
