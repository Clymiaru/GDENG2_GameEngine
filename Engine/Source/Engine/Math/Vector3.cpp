#include "pch.h"
#include "Vector3.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	//----------
	// Vector3Float
	//----------
	Vector3Float::Vector3Float() :
		XMFLOAT3{0.0f, 0.0f, 0.0f}
	{
	}

	Vector3Float::Vector3Float(const float x,
	                           const float y,
	                           const float z) :
		XMFLOAT3{x, y, z}
	{
	}

	Vector3Float::Vector3Float(const XMFLOAT3& v) :
		XMFLOAT3{v}
	{
	}

	Vector3Float::~Vector3Float() = default;

	Vector3Float::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat3(this);
	}

	bool Vector3Float::operator==(const Vector3Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(this);
		const XMVECTOR v2 = XMLoadFloat3(&v);
		return XMVector3Equal(v1, v2);
	}

	bool Vector3Float::operator!=(const Vector3Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(this);
		const XMVECTOR v2 = XMLoadFloat3(&v);
		return XMVector3NotEqual(v1, v2);
	}

	Vector3Float& Vector3Float::operator+=(const Vector3Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR v2     = XMLoadFloat3(&v);
		const XMVECTOR result = XMVectorAdd(v1, v2);
		XMStoreFloat3(this, result);
		return *this;
	}

	Vector3Float& Vector3Float::operator-=(const Vector3Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR v2     = XMLoadFloat3(&v);
		const XMVECTOR result = XMVectorSubtract(v1, v2);
		XMStoreFloat3(this, result);
		return *this;
	}

	Vector3Float& Vector3Float::operator*=(const Vector3Float& v)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR v2     = XMLoadFloat3(&v);
		const XMVECTOR result = XMVectorMultiply(v1, v2);
		XMStoreFloat3(this, result);
		return *this;
	}

	Vector3Float& Vector3Float::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR result = XMVectorScale(v1, s);
		XMStoreFloat3(this, result);
		return *this;
	}

	Vector3Float& Vector3Float::operator/=(const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
		XMStoreFloat3(this, result);
		return *this;
	}

	Vector3Float Vector3Float::operator+() const
	{
		return *this;
	}

	Vector3Float Vector3Float::operator-() const
	{
		return Vector3Float(-x, -y, -z);
	}

	Vector3Float operator+(const Vector3Float& v1,
	                       const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator-(const Vector3Float& v1,
	                       const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator*(const Vector3Float& v1,
	                       const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator*(const Vector3Float& v,
	                       const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator/(const Vector3Float& v1,
	                       const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator/(const Vector3Float& v,
	                       const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadFloat3(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	float Vector3Float::Length() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR result = XMVector3Length(v1);
		return XMVectorGetX(result);
	}

	float Vector3Float::LengthSquared() const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR result = XMVector3LengthSq(v1);
		return XMVectorGetX(result);
	}

	float Vector3Float::Dot(const Vector3Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR v2     = XMLoadFloat3(&v);
		const XMVECTOR result = XMVector3Dot(v1, v2);
		return XMVectorGetX(result);
	}

	Vector3Float Vector3Float::Cross(const Vector3Float& v) const
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadFloat3(this);
		const XMVECTOR v2         = XMLoadFloat3(&v);
		const XMVECTOR tempResult = XMVector3Cross(v1, v2);

		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	void Vector3Float::Normalize()
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(this);
		const XMVECTOR result = XMVector3Normalize(v1);
		XMStoreFloat3(this, result);
	}

	float Vector3Float::Distance(const Vector3Float& v1,
	                             const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat3(&v1);
		const XMVECTOR x2     = XMLoadFloat3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3Length(net);
		return XMVectorGetX(result);
	}

	float Vector3Float::DistanceSquared(const Vector3Float& v1,
	                                    const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat3(&v1);
		const XMVECTOR x2     = XMLoadFloat3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector3Float Vector3Float::Min(const Vector3Float& v1,
	                               const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat3(&v1);
		const XMVECTOR x2  = XMLoadFloat3(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector3Float result;
		XMStoreFloat3(&result, min);
		return result;
	}

	Vector3Float Vector3Float::Max(const Vector3Float& v1,
	                               const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat3(&v1);
		const XMVECTOR x2  = XMLoadFloat3(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector3Float result;
		XMStoreFloat3(&result, max);
		return result;
	}

	Vector3Float Vector3Float::Lerp(const Vector3Float& v1,
	                                const Vector3Float& v2,
	                                const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadFloat3(&v1);
		const XMVECTOR x2         = XMLoadFloat3(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector3Float result;
		XMStoreFloat3(&result, lerpVector);
		return result;
	}

	//----------
	// Vector3Int
	//----------
	Vector3Int::Vector3Int() :
		XMINT3{0, 0, 0}
	{
	}

	Vector3Int::Vector3Int(int32_t x,
	                       int32_t y,
	                       int32_t z) :
		XMINT3{x, y, z}
	{
	}

	Vector3Int::Vector3Int(const XMINT3& v) :
		XMINT3{v}
	{
	}

	Vector3Int::~Vector3Int() = default;

	Vector3Int::operator DirectX::XMVECTOR() const
	{
		return XMLoadSInt3(this);
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

	//----------
	// Vector3Uint
	//----------

	Vector3Uint::Vector3Uint() :
		XMUINT3{0ULL, 0ULL, 0LL}
	{
	}

	Vector3Uint::Vector3Uint(const uint32_t x,
	                         const uint32_t y,
	                         const uint32_t z) :
		XMUINT3{x, y, z}
	{
	}

	Vector3Uint::Vector3Uint(const XMUINT3& v) :
		XMUINT3{v}
	{
	}

	Vector3Uint::~Vector3Uint() = default;

	Vector3Uint::operator DirectX::XMVECTOR() const
	{
		return XMLoadUInt3(this);
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

	Vector3Uint operator+(const Vector3Uint& v1,
	                      const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator-(const Vector3Uint& v1,
	                      const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator*(const Vector3Uint& v1,
	                      const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator*(const Vector3Uint& v,
	                      float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator/(const Vector3Uint& v1,
	                      const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt3(&v1);
		const XMVECTOR tempV2     = XMLoadUInt3(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

	Vector3Uint operator/(const Vector3Uint& v,
	                      float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadUInt3(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector3Uint result;
		XMStoreUInt3(&result, tempResult);
		return result;
	}

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

	float Vector3Uint::Distance(const Vector3Uint& v1,
	                            const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt3(&v1);
		const XMVECTOR x2     = XMLoadUInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3Length(net);
		return XMVectorGetX(result);
	}

	float Vector3Uint::DistanceSquared(const Vector3Uint& v1,
	                                   const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt3(&v1);
		const XMVECTOR x2     = XMLoadUInt3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector3Uint Vector3Uint::Min(const Vector3Uint& v1,
	                             const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt3(&v1);
		const XMVECTOR x2  = XMLoadUInt3(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector3Uint result;
		XMStoreUInt3(&result, min);
		return result;
	}

	Vector3Uint Vector3Uint::Max(const Vector3Uint& v1,
	                             const Vector3Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt3(&v1);
		const XMVECTOR x2  = XMLoadUInt3(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector3Uint result;
		XMStoreUInt3(&result, max);
		return result;
	}

	Vector3Uint Vector3Uint::Lerp(const Vector3Uint& v1,
	                              const Vector3Uint& v2,
	                              const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadUInt3(&v1);
		const XMVECTOR x2         = XMLoadUInt3(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector3Uint result;
		XMStoreUInt3(&result, lerpVector);
		return result;
	}
}