#include "pch.h"
#include "Math.h"
#include "Engine/Core/Debug.h"

namespace Engine
{
	Vector2Float Vector2Float::Zero = Vector2Float(0.0f, 0.0f);
	Vector2Float Vector2Float::One  = Vector2Float(1.0f, 1.0f);

	Vector2Int Vector2Int::Zero = Vector2Int(0, 0);
	Vector2Int Vector2Int::One  = Vector2Int(1, 1);

	Vector2Uint Vector2Uint::Zero = Vector2Uint(0, 0);
	Vector2Uint Vector2Uint::One  = Vector2Uint(1, 1);

	Vector3Float Vector3Float::Zero = Vector3Float(0.0f, 0.0f, 0.0f);
	Vector3Float Vector3Float::One  = Vector3Float(1.0f, 1.0f, 1.0f);

	Vector3Int Vector3Int::Zero = Vector3Int(0, 0, 0);
	Vector3Int Vector3Int::One  = Vector3Int(1, 1, 1);

	Vector3Uint Vector3Uint::Zero = Vector3Uint(0, 0, 0);
	Vector3Uint Vector3Uint::One  = Vector3Uint(1, 1, 1);

	//--------------------------------//
	// Vector2                        //
	//--------------------------------//
	Vector2Float::Vector2Float() :
		XMFLOAT2{0.0f, 0.0f} { }

	Vector2Float::Vector2Float(const float x, const float y) :
		XMFLOAT2{x, y} { }

	Vector2Float::Vector2Float(const XMFLOAT2& v) :
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

	std::ostream& operator<<(std::ostream& os, const Vector2Float& v)
	{
		os << "{" << v.x << ", " << v.y << "}";
		return os;
	}

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

	std::ostream& operator<<(std::ostream& os, const Vector2Int& v)
	{
		os << "{" << v.x << ", " << v.y << "}";
		return os;
	}

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

	std::ostream& operator<<(std::ostream& os, const Vector2Uint& v)
	{
		os << "{" << v.x << ", " << v.y << "}";
		return os;
	}

	//--------------------------------//
	// Vector3                        //
	//--------------------------------//
	Vector3Float::Vector3Float() :
		XMFLOAT3{0.0f, 0.0f, 0.0f} { }

	Vector3Float::Vector3Float(const float x, const float y, const float z) :
		XMFLOAT3{x, y, z} { }

	Vector3Float::Vector3Float(const XMFLOAT3& v) :
		XMFLOAT3{v} { }

	Vector3Float::~Vector3Float() = default;

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

	float Vector3Float::Distance(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat3(&v1);
		const XMVECTOR x2     = XMLoadFloat3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3Length(net);
		return XMVectorGetX(result);
	}

	float Vector3Float::DistanceSquared(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1     = XMLoadFloat3(&v1);
		const XMVECTOR x2     = XMLoadFloat3(&v2);
		const XMVECTOR net    = XMVectorSubtract(x2, x1);
		const XMVECTOR result = XMVector3LengthSq(net);
		return XMVectorGetX(result);
	}

	Vector3Float Vector3Float::Min(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat3(&v1);
		const XMVECTOR x2  = XMLoadFloat3(&v2);
		const XMVECTOR min = XMVectorMin(x1, x2);

		Vector3Float result;
		XMStoreFloat3(&result, min);
		return result;
	}

	Vector3Float Vector3Float::Max(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR x1  = XMLoadFloat3(&v1);
		const XMVECTOR x2  = XMLoadFloat3(&v2);
		const XMVECTOR max = XMVectorMax(x1, x2);

		Vector3Float result;
		XMStoreFloat3(&result, max);
		return result;
	}

	Vector3Float Vector3Float::Lerp(const Vector3Float& v1, const Vector3Float& v2, const float t)
	{
		using namespace DirectX;
		const XMVECTOR x1         = XMLoadFloat3(&v1);
		const XMVECTOR x2         = XMLoadFloat3(&v2);
		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);

		Vector3Float result;
		XMStoreFloat3(&result, lerpVector);
		return result;
	}

	Vector3Float::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat3(this);
	}

	Vector3Float::operator float*() const
	{
		return (float*)this;
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

	Vector3Float operator+(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator-(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator*(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator*(const Vector3Float& v, const float s)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v);
		const XMVECTOR tempResult = XMVectorScale(tempV1, s);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator/(const Vector3Float& v1, const Vector3Float& v2)
	{
		using namespace DirectX;
		const XMVECTOR tempV1     = XMLoadFloat3(&v1);
		const XMVECTOR tempV2     = XMLoadFloat3(&v2);
		const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	Vector3Float operator/(const Vector3Float& v, const float s)
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
		const XMVECTOR v1         = XMLoadFloat3(&v);
		const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
		Vector3Float result;
		XMStoreFloat3(&result, tempResult);
		return result;
	}

	std::ostream& operator<<(std::ostream& os, const Vector3Float& v)
	{
		os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
		return os;
	}

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

	std::ostream& operator<<(std::ostream& os, const Vector3Int& v)
	{
		os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
		return os;
	}

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

	std::ostream& operator<<(std::ostream& os, const Vector3Uint& v)
	{
		os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
		return os;
	}

	//--------------------------------//
	// Matrix                         //
	//--------------------------------//
	// 4x4 Matrix (assumes right-handed cooordinates)
	Matrix4::Matrix4() :
		XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f,
		           0.0f, 1.f, 0.0f, 0.0f,
		           0.0f, 0.0f, 1.0f, 0.0f,
		           0.0f, 0.0f, 0.0f, 1.0f) { }

	Matrix4::Matrix4(const Vector3Float& r0, const Vector3Float& r1, const Vector3Float& r2) :
		XMFLOAT4X4(r0.x, r0.y, r0.z, 0.0f,
		           r1.x, r1.y, r1.z, 0.0f,
		           r2.x, r2.y, r2.z, 0.0f,
		           0.0f, 0.0f, 0.0f, 1.0f) { }

	Matrix4::~Matrix4() = default;

	Matrix4::operator DirectX::XMMATRIX() const
	{
		return XMLoadFloat4x4(this);
	}

	bool Matrix4::operator==(const Matrix4& m) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		return (XMVector4Equal(x1, y1)
		        && XMVector4Equal(x2, y2)
		        && XMVector4Equal(x3, y3)
		        && XMVector4Equal(x4, y4)) != 0;
	}

	bool Matrix4::operator!=(const Matrix4& m) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		return (XMVector4NotEqual(x1, y1)
		        || XMVector4NotEqual(x2, y2)
		        || XMVector4NotEqual(x3, y3)
		        || XMVector4NotEqual(x4, y4)) != 0;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Engine::Matrix4& Engine::Matrix4::operator-=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		const XMMATRIX m1     = XMLoadFloat4x4(this);
		const XMMATRIX m2     = XMLoadFloat4x4(&m);
		const XMMATRIX result = XMMatrixMultiply(m1, m2);
		XMStoreFloat4x4(this, result);
		return *this;
	}

	Matrix4& Matrix4::operator*=(float s) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		x1 = XMVectorScale(x1, s);
		x2 = XMVectorScale(x2, s);
		x3 = XMVectorScale(x3, s);
		x4 = XMVectorScale(x4, s);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator/=(const float s) noexcept
	{
		using namespace DirectX;
		Debug::Assert(s != 0.f, "Attempting to divide by 0!");
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const float rs = 1.0f / s;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator/=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4 Matrix4::operator-() const noexcept
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		v1 = XMVectorNegate(v1);
		v2 = XMVectorNegate(v2);
		v3 = XMVectorNegate(v3);
		v4 = XMVectorNegate(v4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), v1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), v2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), v3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), v4);
		return result;
	}

	Matrix4 Matrix4::Transpose() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX m = XMLoadFloat4x4(this);
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranspose(m));
		return result;
	}

	float Matrix4::Determinant() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX m = XMLoadFloat4x4(this);
		return XMVectorGetX(XMMatrixDeterminant(m));
	}

	Matrix4 Matrix4::CreateTranslation(const Vector3Float& position) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranslation(position.x, position.y, position.z));
		return result;
	}

	Matrix4 Matrix4::CreateTranslation(float x,
	                                   float y,
	                                   float z) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranslation(x, y, z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(const Vector3Float& scales) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(scales.x, scales.y, scales.z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(const float x,
	                             const float y,
	                             const float z) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(x, y, z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(float scale) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(scale, scale, scale));
		return result;
	}

	Matrix4 Matrix4::CreateRotationX(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationX(radians));
		return result;
	}

	Matrix4 Matrix4::CreateRotationY(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationY(radians));
		return result;
	}

	Matrix4 Matrix4::CreateRotationZ(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationZ(radians));
		return result;
	}

	Matrix4 Matrix4::CreatePerspectiveFieldOfView(float fov,
	                                              float aspectRatio,
	                                              float nearPlane,
	                                              float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane));
		return result;
	}

	Matrix4 Matrix4::CreatePerspective(float width,
	                                   float height,
	                                   float nearPlane,
	                                   float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixPerspectiveLH(width, height, nearPlane, farPlane));
		return result;
	}

	Matrix4 Matrix4::CreateOrthographic(float width,
	                                    float height,
	                                    float zNearPlane,
	                                    float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixOrthographicLH(width, height, zNearPlane, zFarPlane));
		return result;
	}

	Matrix4 Matrix4::CreateLookAt(Vector3Float eye, Vector3Float focus, Vector3Float up)
	{
		using namespace DirectX;

		const XMVECTOR x1 = XMLoadFloat3(&eye);
		const XMVECTOR x2 = XMLoadFloat3(&focus);
		const XMVECTOR x3 = XMLoadFloat3(&up);

		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixLookAtLH(x1, x2, x3));
		return result;
	}

	Matrix4 Engine::operator+(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator-(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator*(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		const XMMATRIX tempM1  = XMLoadFloat4x4(&m1);
		const XMMATRIX tempM2  = XMLoadFloat4x4(&m2);
		const XMMATRIX product = XMMatrixMultiply(tempM1, tempM2);

		Matrix4 result;
		XMStoreFloat4x4(&result, product);
		return result;
	}

	Matrix4 Engine::operator*(const Matrix4& m,
	                          float s) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorScale(x1, s);
		x2 = XMVectorScale(x2, s);
		x3 = XMVectorScale(x3, s);
		x4 = XMVectorScale(x4, s);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator/(const Matrix4& m,
	                          float s) noexcept
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		const float rs = 1.0f / s;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Engine::Matrix4 Engine::operator/(const Matrix4& m1,
	                                  const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	//--------------------------------//
	// Color                          //
	//--------------------------------//
	Color::Color() :
		XMFLOAT4{0.0f, 0.0f, 0.0f, 1.0f} { }

	Color::Color(const float red, const float green, const float blue) :
		XMFLOAT4{red, green, blue, 1.0f} { }

	Color::Color(const float red, const float green, const float blue, const float alpha) :
		XMFLOAT4{red, green, blue, alpha} { }

	Color::Color(const Vector3Float& rgbColor) :
		XMFLOAT4{rgbColor.x, rgbColor.y, rgbColor.z, 1.0f} { }

	Color::Color(const XMFLOAT4& rgbaColor) :
		XMFLOAT4{rgbaColor.x, rgbaColor.y, rgbaColor.z, rgbaColor.w} { }

	Color::~Color() = default;

	float Color::Red() const
	{
		return x;
	}

	void Color::Red(const float red)
	{
		x = red;
	}

	float Color::Green() const
	{
		return y;
	}

	void Color::Green(const float green)
	{
		y = green;
	}

	float Color::Blue() const
	{
		return z;
	}

	void Color::Blue(const float blue)
	{
		z = blue;
	}

	float Color::Alpha() const
	{
		return w;
	}

	void Color::Alpha(const float alpha)
	{
		w = alpha;
	}

	Color Color::Lerp(const Color& c1, const Color& c2, const float t) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);

		Color result;
		XMStoreFloat4(&result, XMVectorLerp(tempC1, tempC2, t));
		return result;
	}

	Color::operator DirectX::XMVECTOR() const
	{
		return XMLoadFloat4(this);
	}

	Color::operator float*() const
	{
		return (float*)this;
	}

	bool Color::operator==(const Color& c) const
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorEqual(c1, c2);
	}

	bool Color::operator!=(const Color& c) const
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorNotEqual(c1, c2);
	}

	Color& Color::operator+=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorAdd(c1, c2));
		return *this;
	}

	Color& Color::operator-=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorSubtract(c1, c2));
		return *this;
	}

	Color& Color::operator*=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorMultiply(c1, c2));
		return *this;
	}

	Color& Color::operator*=(const float s)
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(c, s));
		return *this;
	}

	Color& Color::operator/=(const Color& c)
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(this);
		const XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorDivide(c1, c2));
		return *this;
	}

	Color Color::operator-() const
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(this);
		Color result;
		XMStoreFloat4(&result, XMVectorNegate(c));
		return result;
	}

	Color Color::operator+() const
	{
		return *this;
	}

	Color Engine::operator+(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorAdd(tempC1, tempC2));
		return result;
	}

	Color Engine::operator-(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorSubtract(tempC1, tempC2));
		return result;
	}

	Color Engine::operator*(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorMultiply(tempC1, tempC2));
		return result;
	}

	Color Engine::operator*(const Color& c, const float s) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempColor = XMLoadFloat4(&c);
		Color result;
		XMStoreFloat4(&result, XMVectorScale(tempColor, s));
		return result;
	}

	Color Engine::operator/(const Color& c1, const Color& c2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR tempC1 = XMLoadFloat4(&c1);
		const XMVECTOR tempC2 = XMLoadFloat4(&c2);
		Color result;
		XMStoreFloat4(&result, XMVectorDivide(tempC1, tempC2));
		return result;
	}

	std::ostream& operator<<(std::ostream& os, const Color& c)
	{
		os << "{" << c.Red() << ", " << c.Green() << ", " << c.Blue() << ", " << c.Alpha() << "}";
		return os;
	}
}
