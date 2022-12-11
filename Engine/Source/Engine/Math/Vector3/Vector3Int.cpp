#include "pch.h"
#include "Vector3Int.h"

namespace Engine
{
	Vector3Int Vector3Int::Zero = Vector3Int(0, 0, 0);
	Vector3Int Vector3Int::One  = Vector3Int(1, 1, 1);

	Vector3Int::Vector3Int() :
		XMINT3{0, 0, 0} { }

	Vector3Int::Vector3Int(const int32_t x, const int32_t y, const int32_t z) :
		XMINT3{x, y, z} { }

	Vector3Int::Vector3Int(const XMINT3& v) :
		XMINT3{v} { }

	Vector3Int::~Vector3Int() = default;

	float Vector3Int::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR result = XMVector3Length(v1);
		return XMVectorGetX(result);
	}

	float Vector3Int::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR result = XMVector3LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector3Int::Dot(const Vector3Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR v2     = XMLoadSInt3(&v);
		const XMVECTOR result = XMVector3Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector3Int Vector3Int::Cross(const Vector3Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadSInt3(this);
		const XMVECTOR v2         = XMLoadSInt3(&v);
		const XMVECTOR tempResult = XMVector3Cross(v1, v2);

		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	void Vector3Int::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR result = XMVector3Normalize(v1);
		XMStoreSInt3(this, result);
	}

	float Vector3Int::Distance(const Vector3Int& v1,
	                           const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt3(&v1);
		const XMVECTOR x2     = XMLoadSInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3Length(net);
		return XMVectorGetX(result);
	}

	float Vector3Int::DistanceSquared(const Vector3Int& v1,
	                                  const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt3(&v1);
		const XMVECTOR x2     = XMLoadSInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector3Int Vector3Int::Min(const Vector3Int& v1,
	                           const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt3(&v1);
		const XMVECTOR x2  = XMLoadSInt3(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector3Int result;
		XMStoreSInt3(&result, min);
		return result;
	}

	Vector3Int Vector3Int::Max(const Vector3Int& v1,
	                           const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt3(&v1);
		const XMVECTOR x2  = XMLoadSInt3(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector3Int result;
		XMStoreSInt3(&result, max);
		return result;
	}

	Vector3Int Vector3Int::Lerp(const Vector3Int& v1,
	                            const Vector3Int& v2,
	                            const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadSInt3(&v1);
		const XMVECTOR x2         = XMLoadSInt3(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector3Int result;
		XMStoreSInt3(&result, lerpVector);
		return result;
	}

	Vector3Int::operator DirectX::XMVECTOR() const
	{
		return XMLoadSInt3(this);
	}

	Vector3Int::operator int32_t*() const
	{
		return (int*)this;
	}

	bool Vector3Int::operator==(const Vector3Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadSInt3(this);
		const XMVECTOR v2 = XMLoadSInt3(&v);
		return XMVector3Equal(v1, v2);
	}

	bool Vector3Int::operator!=(const Vector3Int& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadSInt3(this);
		const XMVECTOR v2 = XMLoadSInt3(&v);
		return XMVector3NotEqual(v1, v2);
	}

	Vector3Int& Vector3Int::operator+=(const Vector3Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR v2     = XMLoadSInt3(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreSInt3(this, result);
		return *this;
	}

	Vector3Int& Vector3Int::operator-=(const Vector3Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR v2     = XMLoadSInt3(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreSInt3(this, result);
		return *this;
	}

	Vector3Int& Vector3Int::operator*=(const Vector3Int& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR v2     = XMLoadSInt3(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreSInt3(this, result);
		return *this;
	}

	Vector3Int& Vector3Int::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreSInt3(this, result);
		return *this;
	}

	Vector3Int& Vector3Int::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadSInt3(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreSInt3(this, result);
		return *this;
	}

	Vector3Int Vector3Int::operator+() const
	{
		return *this;
	}

	Vector3Int Vector3Int::operator-() const
	{
		return Vector3Int(-x, -y, -z);
	}

	Vector3Int operator+(const Vector3Int& v1,
	                     const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt3(&v1);
		const XMVECTOR tempV2     = XMLoadSInt3(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	Vector3Int operator-(const Vector3Int& v1,
	                     const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt3(&v1);
		const XMVECTOR tempV2     = XMLoadSInt3(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	Vector3Int operator*(const Vector3Int& v1,
	                     const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt3(&v1);
		const XMVECTOR tempV2     = XMLoadSInt3(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	Vector3Int operator*(const Vector3Int& v,
	                     const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	Vector3Int operator/(const Vector3Int& v1,
	                     const Vector3Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt3(&v1);
		const XMVECTOR tempV2     = XMLoadSInt3(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	Vector3Int operator/(const Vector3Int& v,
	                     float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadSInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector3Int result;
		XMStoreSInt3(&result, tempResult);
		return result;
	}

	// std::ostream& operator<<(std::ostream& os, const Vector3Int& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
	// 	return os;
	// }
}