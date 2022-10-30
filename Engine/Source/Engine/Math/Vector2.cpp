#include "pch.h"
#include "Vector2.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	//----------
	// Vector2Float
	//----------
	Vector2Float::Vector2Float() :
		XMFLOAT2{0.0f, 0.0f}
	{
	}

	Vector2Float::Vector2Float(const float x,
	                           const float y) :
		XMFLOAT2{x, y}
	{
	}

	Vector2Float::Vector2Float(const XMFLOAT2& v) :
		XMFLOAT2{v}
	{
	}

	Vector2Float::~Vector2Float() = default;

	Vector2Float::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat2(this);
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

	Vector2Float operator+(const Vector2Float& v1,
	                       const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator-(const Vector2Float& v1,
	                       const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator*(const Vector2Float& v1,
	                       const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator*(const Vector2Float& v,
	                       const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator/(const Vector2Float& v1,
	                       const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat2(&v1);
		const XMVECTOR tempV2     = XMLoadFloat2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

	Vector2Float operator/(const Vector2Float& v,
	                       const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadFloat2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Float result;
		XMStoreFloat2(&result, tempResult);
		return result;
	}

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

	float Vector2Float::Distance(const Vector2Float& v1,
	                             const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat2(&v1);
		const XMVECTOR x2     = XMLoadFloat2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Float::DistanceSquared(const Vector2Float& v1,
	                                    const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat2(&v1);
		const XMVECTOR x2     = XMLoadFloat2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Float Vector2Float::Min(const Vector2Float& v1,
	                               const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat2(&v1);
		const XMVECTOR x2  = XMLoadFloat2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Float result;
		XMStoreFloat2(&result, min);
		return result;
	}

	Vector2Float Vector2Float::Max(const Vector2Float& v1,
	                               const Vector2Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat2(&v1);
		const XMVECTOR x2  = XMLoadFloat2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Float result;
		XMStoreFloat2(&result, max);
		return result;
	}

	Vector2Float Vector2Float::Lerp(const Vector2Float& v1,
	                                const Vector2Float& v2,
	                                const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadFloat2(&v1);
		const XMVECTOR x2         = XMLoadFloat2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Float result;
		XMStoreFloat2(&result, lerpVector);
		return result;
	}

	//----------
	// Vector2Int
	//----------

	Vector2Int::Vector2Int() :
		XMINT2{0, 0}
	{
	}

	Vector2Int::Vector2Int(int32_t x,
	                       int32_t y) :
		XMINT2{x, y}
	{
	}

	Vector2Int::Vector2Int(const XMINT2& v) :
		XMINT2{v}
	{
	}

	Vector2Int::~Vector2Int() = default;

	Vector2Int::operator DirectX::XMVECTOR() const
	{
		return XMLoadSInt2(this);
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

	Vector2Int operator+(const Vector2Int& v1,
	                     const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator-(const Vector2Int& v1,
	                     const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator*(const Vector2Int& v1,
	                     const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator*(const Vector2Int& v,
	                     const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator/(const Vector2Int& v1,
	                     const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadSInt2(&v1);
		const XMVECTOR tempV2     = XMLoadSInt2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

	Vector2Int operator/(const Vector2Int& v,
	                     float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadSInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Int result;
		XMStoreSInt2(&result, tempResult);
		return result;
	}

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

	float Vector2Int::Distance(const Vector2Int& v1,
	                           const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt2(&v1);
		const XMVECTOR x2     = XMLoadSInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Int::DistanceSquared(const Vector2Int& v1,
	                                  const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadSInt2(&v1);
		const XMVECTOR x2     = XMLoadSInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Int Vector2Int::Min(const Vector2Int& v1,
	                           const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt2(&v1);
		const XMVECTOR x2  = XMLoadSInt2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Int result;
		XMStoreSInt2(&result, min);
		return result;
	}

	Vector2Int Vector2Int::Max(const Vector2Int& v1,
	                           const Vector2Int& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadSInt2(&v1);
		const XMVECTOR x2  = XMLoadSInt2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Int result;
		XMStoreSInt2(&result, max);
		return result;
	}

	Vector2Int Vector2Int::Lerp(const Vector2Int& v1,
	                            const Vector2Int& v2,
	                            float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadSInt2(&v1);
		const XMVECTOR x2         = XMLoadSInt2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Int result;
		XMStoreSInt2(&result, lerpVector);
		return result;
	}

	//----------
	// Vector2Uint
	//----------

	Vector2Uint::Vector2Uint() :
		XMUINT2{0ULL, 0ULL}
	{
	}

	Vector2Uint::Vector2Uint(uint32_t x,
	                         uint32_t y) :
		XMUINT2{x, y}
	{
	}

	Vector2Uint::Vector2Uint(const XMUINT2& v) :
		XMUINT2{v}
	{
	}

	Vector2Uint::~Vector2Uint() = default;

	Vector2Uint::operator DirectX::XMVECTOR() const
	{
		return XMLoadUInt2(this);
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

	Vector2Uint operator+(const Vector2Uint& v1,
	                      const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator-(const Vector2Uint& v1,
	                      const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator*(const Vector2Uint& v1,
	                      const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator*(const Vector2Uint& v,
	                      float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator/(const Vector2Uint& v1,
	                      const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadUInt2(&v1);
		const XMVECTOR tempV2     = XMLoadUInt2(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

	Vector2Uint operator/(const Vector2Uint& v,
	                      float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadUInt2(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector2Uint result;
		XMStoreUInt2(&result, tempResult);
		return result;
	}

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

	float Vector2Uint::Distance(const Vector2Uint& v1,
	                            const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt2(&v1);
		const XMVECTOR x2     = XMLoadUInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2Length(net);
		return XMVectorGetX(result);
	}

	float Vector2Uint::DistanceSquared(const Vector2Uint& v1,
	                                   const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadUInt2(&v1);
		const XMVECTOR x2     = XMLoadUInt2(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector2LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector2Uint Vector2Uint::Min(const Vector2Uint& v1,
	                             const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt2(&v1);
		const XMVECTOR x2  = XMLoadUInt2(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector2Uint result;
		XMStoreUInt2(&result, min);
		return result;
	}

	Vector2Uint Vector2Uint::Max(const Vector2Uint& v1,
	                             const Vector2Uint& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadUInt2(&v1);
		const XMVECTOR x2  = XMLoadUInt2(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector2Uint result;
		XMStoreUInt2(&result, max);
		return result;
	}

	Vector2Uint Vector2Uint::Lerp(const Vector2Uint& v1,
	                              const Vector2Uint& v2,
	                              const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadUInt2(&v1);
		const XMVECTOR x2         = XMLoadUInt2(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector2Uint result;
		XMStoreUInt2(&result, lerpVector);
		return result;
	}
}
