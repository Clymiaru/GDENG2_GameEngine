#pragma once
#include <DirectXMath.h>

namespace Engine
{
	// template <typename T>
	// struct Vector2
	// {
	// };
	//
	// //---------- Vector2 Float
	// template <>
	// struct Vector2<float> final : DirectX::XMFLOAT2
	// {
	// 	Vector2() :
	// 		XMFLOAT2{0.0f, 0.0f}
	// 	{
	// 	}
	//
	// 	~Vector2() = default;
	//
	// 	explicit Vector2(float x,
	// 	                 float y) :
	// 		XMFLOAT2(x, y)
	// 	{
	// 	}
	//
	// 	explicit Vector2(const XMFLOAT2& v) :
	// 		XMFLOAT2{v}
	// 	{
	// 	}
	//
	// 	Vector2(const Vector2&) = default;
	//
	// 	Vector2& operator=(const Vector2& v) = default;
	//
	// 	Vector2(Vector2&&) noexcept = default;
	//
	// 	Vector2& operator=(Vector2&&) noexcept = default;
	//
	// 	explicit operator DirectX::XMVECTOR() const
	// 	{
	// 		return XMLoadFloat2(this);
	// 	}
	//
	// 	bool operator ==(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadFloat2(this);
	// 		const XMVECTOR v2 = XMLoadFloat2(&v);
	// 		return XMVector2Equal(v1, v2);
	// 	}
	//
	// 	bool operator !=(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadFloat2(this);
	// 		const XMVECTOR v2 = XMLoadFloat2(&v);
	// 		return XMVector2NotEqual(v1, v2);
	// 	}
	//
	// 	Vector2& operator+=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadFloat2(this);
	// 		const XMVECTOR v2     = XMLoadFloat2(&v);
	// 		const XMVECTOR result = XMVectorAdd(v1, v2);
	// 		XMStoreFloat2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator-=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadFloat2(this);
	// 		const XMVECTOR v2     = XMLoadFloat2(&v);
	// 		const XMVECTOR result = XMVectorSubtract(v1, v2);
	// 		XMStoreFloat2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadFloat2(this);
	// 		const XMVECTOR v2     = XMLoadFloat2(&v);
	// 		const XMVECTOR result = XMVectorMultiply(v1, v2);
	// 		XMStoreFloat2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadFloat2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, s);
	// 		XMStoreFloat2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator/=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		//ENGINE_ASSERT(s != 0.0f, "Attempting to divide by 0!");
	// 		const XMVECTOR v1     = XMLoadFloat2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
	// 		XMStoreFloat2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2 operator+() const;
	//
	// 	Vector2 operator-() const;
	//
	// 	[[nodiscard]]
	// 	float Length() const;
	//
	// 	[[nodiscard]]
	// 	float LengthSquared() const;
	//
	// 	[[nodiscard]]
	// 	float Dot(const Vector2& v) const;
	//
	// 	[[nodiscard]]
	// 	Vector2 Cross(const Vector2& v) const;
	//
	// 	void Normalize();
	//
	// 	[[nodiscard]]
	// 	static float Distance(const Vector2& v1,
	// 	                      const Vector2& v2);
	//
	// 	[[nodiscard]]
	// 	static float DistanceSquared(const Vector2& v1,
	// 	                             const Vector2& v2);
	//
	// 	[[nodiscard]]
	// 	static Vector2 Min(const Vector2& v1,
	// 	                   const Vector2& v2);
	//
	// 	[[nodiscard]]
	// 	static Vector2 Max(const Vector2& v1,
	// 	                   const Vector2& v2);
	//
	// 	[[nodiscard]]
	// 	static Vector2 Lerp(const Vector2& v1,
	// 	                    const Vector2& v2,
	// 	                    float t);
	//
	// 	static const Vector2 Zero;
	//
	// 	static const Vector2 One;
	//
	// 	static const Vector2 UnitX;
	//
	// 	static const Vector2 UnitY;
	// };
	//
	// Vector2<float> operator+(const Vector2<float>& v1,
	//                          const Vector2<float>& v2);
	//
	// Vector2<float> operator-(const Vector2<float>& v1,
	//                          const Vector2<float>& v2);
	//
	// Vector2<float> operator*(const Vector2<float>& v1,
	//                          const Vector2<float>& v2);
	//
	// Vector2<float> operator*(const Vector2<float>& v,
	//                          float s);
	//
	// Vector2<float> operator/(const Vector2<float>& v1,
	//                          const Vector2<float>& v2);
	//
	// Vector2<float> operator/(const Vector2<float>& v,
	//                          float s);
	//
	// inline Vector2<float> operator+(const Vector2<float>& v1,
	//                                 const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline Vector2<float> operator-(const Vector2<float>& v1,
	//                                 const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline Vector2<float> operator*(const Vector2<float>& v1,
	//                                 const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline Vector2<float> operator*(const Vector2<float>& v,
	//                                 float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1     = XMLoadFloat2(&v);
	// 	const XMVECTOR tempResult = XMVectorScale(tempV1, s);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline Vector2<float> operator/(const Vector2<float>& v1,
	//                                 const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline Vector2<float> operator/(const Vector2<float>& v,
	//                                 float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1         = XMLoadFloat2(&v);
	// 	const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline float Vector2<float>::Length() const
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat2(this);
	// 	const XMVECTOR result = XMVector2Length(v1);
	// 	return XMVectorGetX(result);
	// }
	//
	// inline float Vector2<float>::LengthSquared() const
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat2(this);
	// 	const XMVECTOR result = XMVector2LengthSq(v1);
	// 	return XMVectorGetX(result);
	// }
	//
	// inline float Vector2<float>::Dot(const Vector2<float>& v) const
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat2(this);
	// 	const XMVECTOR v2     = XMLoadFloat2(&v);
	// 	const XMVECTOR result = XMVector2Dot(v1, v2);
	// 	return XMVectorGetX(result);
	// }
	//
	// inline Vector2<float> Vector2<float>::Cross(const Vector2<float>& v) const
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1         = XMLoadFloat2(this);
	// 	const XMVECTOR v2         = XMLoadFloat2(&v);
	// 	const XMVECTOR tempResult = XMVector2Cross(v1, v2);
	//
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, tempResult);
	// 	return result;
	// }
	//
	// inline void Vector2<float>::Normalize()
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat2(this);
	// 	const XMVECTOR result = XMVector2Normalize(v1);
	// 	XMStoreFloat2(this, result);
	// }
	//
	// inline float Vector2<float>::Distance(const Vector2<float>& v1,
	//                                       const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR x1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR x2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 	const XMVECTOR result = XMVector2Length(net);
	// 	return XMVectorGetX(result);
	// }
	//
	// inline float Vector2<float>::DistanceSquared(const Vector2<float>& v1,
	//                                              const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR x1     = XMLoadFloat2(&v1);
	// 	const XMVECTOR x2     = XMLoadFloat2(&v2);
	// 	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 	const XMVECTOR result = XMVector2LengthSq(net);
	// 	return XMVectorGetX(result);
	// }
	//
	// inline Vector2<float> Vector2<float>::Min(const Vector2<float>& v1,
	//                                           const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR x1  = XMLoadFloat2(&v1);
	// 	const XMVECTOR x2  = XMLoadFloat2(&v2);
	// 	const XMVECTOR min = XMVectorMin(x1, x2);
	//
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, min);
	// 	return result;
	// }
	//
	// inline Vector2<float> Vector2<float>::Max(const Vector2<float>& v1,
	//                                           const Vector2<float>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR x1  = XMLoadFloat2(&v1);
	// 	const XMVECTOR x2  = XMLoadFloat2(&v2);
	// 	const XMVECTOR max = XMVectorMax(x1, x2);
	//
	// 	Vector2<float> result;
	// 	XMStoreFloat2(&result, max);
	// 	return result;
	// }
	//
	// inline Vector2<float> Vector2<float>::Lerp(const Vector2<float>& v1,
	//                                            const Vector2<float>& v2,
	//                                            float t)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR x1         = XMLoadFloat2(&v1);
	// 	const XMVECTOR x2         = XMLoadFloat2(&v2);
	// 	const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);
	//
	// 	Vector2 result;
	// 	XMStoreFloat2(&result, lerpVector);
	// 	return result;
	// }
	//
	// inline Vector2<float> Vector2<float>::operator+() const
	// {
	// 	return *this;
	// }
	//
	// inline Vector2<float> Vector2<float>::operator-() const
	// {
	// 	return Vector2(-x, -y);
	// }
	//
	// template <>
	// struct Vector2<int> final : DirectX::XMINT2
	// {
	// 	Vector2() :
	// 		XMINT2{0, 0}
	// 	{
	// 	}
	//
	// 	~Vector2() = default;
	//
	// 	explicit Vector2(int x,
	// 	                 int y) :
	// 		XMINT2{x, y}
	// 	{
	// 	}
	//
	// 	explicit Vector2(const XMINT2& v) :
	// 		XMINT2{v}
	// 	{
	// 	}
	//
	// 	Vector2(const Vector2&) = default;
	//
	// 	Vector2& operator=(const Vector2&) = default;
	//
	// 	Vector2(Vector2&&) noexcept = default;
	//
	// 	Vector2& operator=(Vector2&&) noexcept = default;
	//
	// 	explicit operator DirectX::XMVECTOR() const
	// 	{
	// 		return XMLoadSInt2(this);
	// 	}
	//
	// 	bool operator ==(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadSInt2(this);
	// 		const XMVECTOR v2 = XMLoadSInt2(&v);
	// 		return XMVector2Equal(v1, v2);
	// 	}
	//
	// 	bool operator !=(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadSInt2(this);
	// 		const XMVECTOR v2 = XMLoadSInt2(&v);
	// 		return XMVector2NotEqual(v1, v2);
	// 	}
	//
	// 	Vector2& operator+=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR v2     = XMLoadSInt2(&v);
	// 		const XMVECTOR result = XMVectorAdd(v1, v2);
	// 		XMStoreSInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator-=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR v2     = XMLoadSInt2(&v);
	// 		const XMVECTOR result = XMVectorSubtract(v1, v2);
	// 		XMStoreSInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR v2     = XMLoadSInt2(&v);
	// 		const XMVECTOR result = XMVectorMultiply(v1, v2);
	// 		XMStoreSInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, s);
	// 		XMStoreSInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator/=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		//TODO: assert(S != 0.0f);
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
	// 		XMStoreSInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2 operator+() const
	// 	{
	// 		return *this;
	// 	}
	//
	// 	Vector2 operator-() const
	// 	{
	// 		return Vector2<int>(-x, -y);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float Length() const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1           = XMLoadSInt2(this);
	// 		const XMVECTOR lengthVector = XMVector2Length(v1);
	// 		return XMVectorGetX(lengthVector);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float LengthSquared() const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1             = XMLoadSInt2(this);
	// 		const XMVECTOR lengthSqVector = XMVector2LengthSq(v1);
	// 		return XMVectorGetX(lengthSqVector);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float Dot(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadSInt2(this);
	// 		const XMVECTOR v2     = XMLoadSInt2(&v);
	// 		const XMVECTOR result = XMVector2Dot(v1, v2);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	Vector2 Cross(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1    = XMLoadSInt2(this);
	// 		const XMVECTOR v2    = XMLoadSInt2(&v);
	// 		const XMVECTOR cross = XMVector2Cross(v1, v2);
	//
	// 		Vector2<int> result;
	// 		XMStoreSInt2(&result, cross);
	// 		return result;
	// 	}
	//
	// 	void Normalize()
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1         = XMLoadSInt2(this);
	// 		const XMVECTOR normalized = XMVector2Normalize(v1);
	// 		XMStoreSInt2(this, normalized);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static float Distance(const Vector2& v1,
	// 	                      const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1     = XMLoadSInt2(&v1);
	// 		const XMVECTOR x2     = XMLoadSInt2(&v2);
	// 		const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 		const XMVECTOR result = XMVector2Length(net);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static float DistanceSquared(const Vector2& v1,
	// 	                             const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1     = XMLoadSInt2(&v1);
	// 		const XMVECTOR x2     = XMLoadSInt2(&v2);
	// 		const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 		const XMVECTOR result = XMVector2LengthSq(net);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Min(const Vector2& v1,
	// 	                   const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1  = XMLoadSInt2(&v1);
	// 		const XMVECTOR x2  = XMLoadSInt2(&v2);
	// 		const XMVECTOR min = XMVectorMin(x1, x2);
	//
	// 		Vector2<int> result;
	// 		XMStoreSInt2(&result, min);
	// 		return result;
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Max(const Vector2& v1,
	// 	                   const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1  = XMLoadSInt2(&v1);
	// 		const XMVECTOR x2  = XMLoadSInt2(&v2);
	// 		const XMVECTOR max = XMVectorMax(x1, x2);
	//
	// 		Vector2<int> result;
	// 		XMStoreSInt2(&result, max);
	// 		return result;
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Lerp(const Vector2& v1,
	// 	                    const Vector2& v2,
	// 	                    float t)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1         = XMLoadSInt2(&v1);
	// 		const XMVECTOR x2         = XMLoadSInt2(&v2);
	// 		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);
	//
	// 		Vector2<int> result;
	// 		XMStoreSInt2(&result, lerpVector);
	// 		return result;
	// 	}
	//
	// 	static const Vector2<int> Zero;
	//
	// 	static const Vector2<int> One;
	//
	// 	static const Vector2<int> UnitX;
	//
	// 	static const Vector2<int> UnitY;
	// };
	//
	// inline Vector2<int> operator+(const Vector2<int>& v1,
	//                               const Vector2<int>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadSInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadSInt2(&v2);
	// 	const XMVECTOR net    = XMVectorAdd(tempV1, tempV2);
	// 	Vector2<int> result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<int> operator-(const Vector2<int>& v1,
	//                               const Vector2<int>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadSInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadSInt2(&v2);
	// 	const XMVECTOR net    = XMVectorSubtract(tempV1, tempV2);
	// 	Vector2<int> result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<int> operator*(const Vector2<int>& v1,
	//                               const Vector2<int>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadSInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadSInt2(&v2);
	// 	const XMVECTOR net    = XMVectorMultiply(tempV1, tempV2);
	// 	Vector2<int> result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<int> operator*(const Vector2<int>& v,
	//                               float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadSInt2(&v);
	// 	const XMVECTOR net = XMVectorScale(v1, s);
	// 	Vector2 result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<int> operator/(const Vector2<int>& v1,
	//                               const Vector2<int>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadSInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadSInt2(&v2);
	// 	const XMVECTOR net    = XMVectorDivide(tempV1, tempV2);
	// 	Vector2<int> result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<int> operator/(const Vector2<int>& v,
	//                               float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadSInt2(&v);
	// 	const XMVECTOR net = XMVectorScale(v1, 1.0f / s);
	// 	Vector2 result;
	// 	XMStoreSInt2(&result, net);
	// 	return result;
	// }
	//
	// template <>
	// struct Vector2<uint32_t> final : DirectX::XMUINT2
	// {
	// 	Vector2() :
	// 		XMUINT2{0U, 0U}
	// 	{
	// 	}
	//
	// 	~Vector2() = default;
	//
	// 	explicit Vector2(uint32_t x,
	// 	                 uint32_t y) :
	// 		XMUINT2{x, y}
	// 	{
	// 	}
	//
	// 	explicit Vector2(const XMUINT2& v) :
	// 		XMUINT2{v}
	// 	{
	// 	}
	//
	// 	Vector2(const Vector2&) = default;
	//
	// 	Vector2& operator=(const Vector2&) = default;
	//
	// 	Vector2(Vector2&&) noexcept = default;
	//
	// 	Vector2& operator=(Vector2&&) noexcept = default;
	//
	// 	explicit operator DirectX::XMVECTOR() const
	// 	{
	// 		return XMLoadUInt2(this);
	// 	}
	//
	// 	bool operator ==(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadUInt2(this);
	// 		const XMVECTOR v2 = XMLoadUInt2(&v);
	// 		return XMVector2Equal(v1, v2);
	// 	}
	//
	// 	bool operator !=(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1 = XMLoadUInt2(this);
	// 		const XMVECTOR v2 = XMLoadUInt2(&v);
	// 		return XMVector2NotEqual(v1, v2);
	// 	}
	//
	// 	Vector2& operator+=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR v2     = XMLoadUInt2(&v);
	// 		const XMVECTOR result = XMVectorAdd(v1, v2);
	// 		XMStoreUInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator-=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR v2     = XMLoadUInt2(&v);
	// 		const XMVECTOR result = XMVectorSubtract(v1, v2);
	// 		XMStoreUInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(const Vector2& v)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR v2     = XMLoadUInt2(&v);
	// 		const XMVECTOR result = XMVectorMultiply(v1, v2);
	// 		XMStoreUInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator*=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, s);
	// 		XMStoreUInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2& operator/=(float s)
	// 	{
	// 		using namespace DirectX;
	// 		//TODO: assert(S != 0.0f);
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
	// 		XMStoreUInt2(this, result);
	// 		return *this;
	// 	}
	//
	// 	Vector2 operator+() const
	// 	{
	// 		return *this;
	// 	}
	//
	// 	Vector2 operator-() const
	// 	{
	// 		return Vector2<uint32_t>(-x, -y);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float Length() const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1           = XMLoadUInt2(this);
	// 		const XMVECTOR lengthVector = XMVector2Length(v1);
	// 		return XMVectorGetX(lengthVector);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float LengthSquared() const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1             = XMLoadUInt2(this);
	// 		const XMVECTOR lengthSqVector = XMVector2LengthSq(v1);
	// 		return XMVectorGetX(lengthSqVector);
	// 	}
	//
	// 	[[nodiscard]]
	// 	float Dot(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1     = XMLoadUInt2(this);
	// 		const XMVECTOR v2     = XMLoadUInt2(&v);
	// 		const XMVECTOR result = XMVector2Dot(v1, v2);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	Vector2 Cross(const Vector2& v) const
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1    = XMLoadUInt2(this);
	// 		const XMVECTOR v2    = XMLoadUInt2(&v);
	// 		const XMVECTOR cross = XMVector2Cross(v1, v2);
	//
	// 		Vector2<uint32_t> result;
	// 		XMStoreUInt2(&result, cross);
	// 		return result;
	// 	}
	//
	// 	void Normalize()
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR v1         = XMLoadUInt2(this);
	// 		const XMVECTOR normalized = XMVector2Normalize(v1);
	// 		XMStoreUInt2(this, normalized);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static float Distance(const Vector2& v1,
	// 	                      const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1     = XMLoadUInt2(&v1);
	// 		const XMVECTOR x2     = XMLoadUInt2(&v2);
	// 		const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 		const XMVECTOR result = XMVector2Length(net);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static float DistanceSquared(const Vector2& v1,
	// 	                             const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1     = XMLoadUInt2(&v1);
	// 		const XMVECTOR x2     = XMLoadUInt2(&v2);
	// 		const XMVECTOR net    = XMVectorSubtract(x2, x1);
	// 		const XMVECTOR result = XMVector2LengthSq(net);
	// 		return XMVectorGetX(result);
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Min(const Vector2& v1,
	// 	                   const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1  = XMLoadUInt2(&v1);
	// 		const XMVECTOR x2  = XMLoadUInt2(&v2);
	// 		const XMVECTOR min = XMVectorMin(x1, x2);
	//
	// 		Vector2<uint32_t> result;
	// 		XMStoreUInt2(&result, min);
	// 		return result;
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Max(const Vector2& v1,
	// 	                   const Vector2& v2)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1  = XMLoadUInt2(&v1);
	// 		const XMVECTOR x2  = XMLoadUInt2(&v2);
	// 		const XMVECTOR max = XMVectorMax(x1, x2);
	//
	// 		Vector2<uint32_t> result;
	// 		XMStoreUInt2(&result, max);
	// 		return result;
	// 	}
	//
	// 	[[nodiscard]]
	// 	static Vector2 Lerp(const Vector2& v1,
	// 	                    const Vector2& v2,
	// 	                    float t)
	// 	{
	// 		using namespace DirectX;
	// 		const XMVECTOR x1         = XMLoadUInt2(&v1);
	// 		const XMVECTOR x2         = XMLoadUInt2(&v2);
	// 		const XMVECTOR lerpVector = XMVectorLerp(x1, x2, t);
	//
	// 		Vector2<uint32_t> result;
	// 		XMStoreUInt2(&result, lerpVector);
	// 		return result;
	// 	}
	//
	// 	static const Vector2<int> Zero;
	//
	// 	static const Vector2<int> One;
	//
	// 	static const Vector2<int> UnitX;
	//
	// 	static const Vector2<int> UnitY;
	// };
	//
	// inline Vector2<uint32_t> operator+(const Vector2<uint32_t>& v1,
	//                                    const Vector2<uint32_t>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadUInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadUInt2(&v2);
	// 	const XMVECTOR net    = XMVectorAdd(tempV1, tempV2);
	// 	Vector2<uint32_t> result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<uint32_t> operator-(const Vector2<uint32_t>& v1,
	//                                    const Vector2<uint32_t>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadUInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadUInt2(&v2);
	// 	const XMVECTOR net    = XMVectorSubtract(tempV1, tempV2);
	// 	Vector2<uint32_t> result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<uint32_t> operator*(const Vector2<uint32_t>& v1,
	//                                    const Vector2<uint32_t>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadUInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadUInt2(&v2);
	// 	const XMVECTOR net    = XMVectorMultiply(tempV1, tempV2);
	// 	Vector2<uint32_t> result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<uint32_t> operator*(const Vector2<uint32_t>& v,
	//                                    float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadUInt2(&v);
	// 	const XMVECTOR net = XMVectorScale(v1, s);
	// 	Vector2 result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<uint32_t> operator/(const Vector2<uint32_t>& v1,
	//                                    const Vector2<uint32_t>& v2)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR tempV1 = XMLoadUInt2(&v1);
	// 	const XMVECTOR tempV2 = XMLoadUInt2(&v2);
	// 	const XMVECTOR net    = XMVectorDivide(tempV1, tempV2);
	// 	Vector2<uint32_t> result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }
	//
	// inline Vector2<uint32_t> operator/(const Vector2<uint32_t>& v,
	//                                    float s)
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadUInt2(&v);
	// 	const XMVECTOR net = XMVectorScale(v1, 1.0f / s);
	// 	Vector2 result;
	// 	XMStoreUInt2(&result, net);
	// 	return result;
	// }

	// template<>
	// struct Vector3<float>
	// {
	// };
	// struct Vector3<int>	(TODO)
	// struct Vector3<uint32_t> (TODO);

	// struct Vector4;
	// struct Matrix4x4 (TODO);
	// struct Quaternion;
	// struct Color (TODO);
	// struct Ray (TODO);
	// struct Viewport (TODO);
	// struct Rect (TODO);

	// class Vector2 final
	// {
	// public:
	// 	Vector2() noexcept;
	//
	// 	constexpr explicit Vector2(const float x,
	// 	                           const float y) noexcept;
	//
	// 	Vector2(const Vector2&) = default;
	//
	// 	Vector2& operator=(const Vector2&) = default;
	//
	// 	Vector2(Vector2&&) = default;
	//
	// 	Vector2& operator=(Vector2&&) = default;
	//
	// 	operator DirectX::XMVECTOR() const noexcept;
	//
	// 	bool operator ==(const Vector2& other) const noexcept;
	//
	// 	bool operator !=(const Vector2& other) const noexcept;
	//
	// 	Vector2& operator+=(const Vector2& other) noexcept;
	//
	// 	Vector2& operator-=(const Vector2& other) noexcept;
	//
	// 	Vector2& operator*=(float scalar) noexcept;
	//
	// 	Vector2& operator/=(float scalar) noexcept;
	//
	// 	Vector2 operator+() const noexcept;
	//
	// 	Vector2 operator-() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float Length() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float LengthSquared() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float Dot(const Vector2& other) const noexcept;
	//
	// 	[[nodiscard]]
	// 	Vector2 Cross(const Vector2& other) const noexcept;
	//
	// 	void Normalize() noexcept;
	//
	// 	[[nodiscard]]
	// 	Vector2 Normalize() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float X() const noexcept;
	//
	// 	void X(float x) noexcept;
	//
	// 	[[nodiscard]]
	// 	float Y() const noexcept;
	//
	// 	void Y(float y) noexcept;
	//
	// 	//----------CONSTANTS
	// 	static const Vector2 Zero;
	//
	// 	static const Vector2 One;
	//
	// 	static const Vector2 UnitX;
	//
	// 	static const Vector2 UnitY;
	//
	// private:
	// 	DirectX::XMFLOAT2 m_Data;
	// };
	//
	// // Vector2 operator+(const Vector2& vector1,
	// //                   const Vector2& vector2) noexcept;
	// //
	// // Vector2 operator-(const Vector2& vector1,
	// //                   const Vector2& vector2) noexcept;
	// //
	// // Vector2 operator*(const Vector2& vector,
	// //                   float scalar) noexcept;
	// //
	// // Vector2 operator/(const Vector2& vector,
	// //                   float scalar) noexcept;
	//
	// // class Vector3 final : DirectX::XMFLOAT3
	// // {
	// // public:
	// // 	Vector3() noexcept;
	// //
	// // 	constexpr explicit Vector3(const float x,
	// // 							   const float y,
	// // 							   const float z) noexcept;
	// //
	// // 	Vector3(const Vector3&) = default;
	// //
	// // 	Vector3& operator=(const Vector3&) = default;
	// //
	// // 	Vector3(Vector3&&) = default;
	// //
	// // 	Vector3& operator=(Vector3&&) = default;
	// //
	// // 	operator DirectX::XMVECTOR() const noexcept;
	// //
	// // 	bool operator ==(const Vector3& other) const noexcept;
	// //
	// // 	bool operator !=(const Vector3& other) const noexcept;
	// //
	// // 	Vector3& operator+=(const Vector3& other) noexcept;
	// //
	// // 	Vector3& operator-=(const Vector3& other) noexcept;
	// //
	// // 	Vector3& operator*=(float scalar) noexcept;
	// //
	// // 	Vector3& operator/=(float scalar) noexcept;
	// //
	// // 	Vector3 operator+() const noexcept;
	// //
	// // 	Vector3 operator-() const noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float Length() const noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float LengthSquared() const noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float Dot(const Vector3& other) const noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	Vector3 Cross(const Vector3& other) const noexcept;
	// //
	// // 	void Normalize() noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	Vector3 Normalize() const noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float X() const noexcept;
	// //
	// // 	void X(float x) noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float Y() const noexcept;
	// //
	// // 	void Y(float y) noexcept;
	// //
	// // 	[[nodiscard]]
	// // 	float Z() const noexcept;
	// //
	// // 	void Z(float z) noexcept;
	// //
	// // 	//----------CONSTANTS
	// // 	static const Vector3 Zero;
	// //
	// // 	static const Vector3 One;
	// //
	// // 	static const Vector3 UnitX;
	// //
	// // 	static const Vector3 UnitY;
	// //
	// // 	static const Vector3 UnitZ;
	// //
	// // 	static const Vector3 Up;
	// //
	// // 	static const Vector3 Down;
	// //
	// // 	static const Vector3 Right;
	// //
	// // 	static const Vector3 Left;
	// //
	// // 	static const Vector3 Forward;
	// //
	// // 	static const Vector3 Backward;
	// // };
	//
	// class Vector3 final
	// {
	// public:
	// 	Vector3() noexcept;
	//
	// 	constexpr explicit Vector3(const float x,
	// 	                           const float y,
	// 	                           const float z) noexcept;
	//
	// 	Vector3(const Vector3&) = default;
	//
	// 	Vector3& operator=(const Vector3&) = default;
	//
	// 	Vector3(Vector3&&) = default;
	//
	// 	Vector3& operator=(Vector3&&) = default;
	//
	// 	operator DirectX::XMVECTOR() const noexcept;
	//
	// 	bool operator ==(const Vector3& other) const noexcept;
	//
	// 	bool operator !=(const Vector3& other) const noexcept;
	//
	// 	Vector3& operator+=(const Vector3& other) noexcept;
	//
	// 	Vector3& operator-=(const Vector3& other) noexcept;
	//
	// 	Vector3& operator*=(float scalar) noexcept;
	//
	// 	Vector3& operator/=(float scalar) noexcept;
	//
	// 	Vector3 operator+() const noexcept;
	//
	// 	Vector3 operator-() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float Length() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float LengthSquared() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float Dot(const Vector3& other) const noexcept;
	//
	// 	[[nodiscard]]
	// 	Vector3 Cross(const Vector3& other) const noexcept;
	//
	// 	void Normalize() noexcept;
	//
	// 	[[nodiscard]]
	// 	Vector3 Normalize() const noexcept;
	//
	// 	[[nodiscard]]
	// 	float X() const noexcept;
	//
	// 	void X(float x) noexcept;
	//
	// 	[[nodiscard]]
	// 	float Y() const noexcept;
	//
	// 	void Y(float y) noexcept;
	//
	// 	[[nodiscard]]
	// 	float Z() const noexcept;
	//
	// 	void Z(float z) noexcept;
	//
	// 	//----------CONSTANTS
	// 	static const Vector3 Zero;
	//
	// 	static const Vector3 One;
	//
	// 	static const Vector3 UnitX;
	//
	// 	static const Vector3 UnitY;
	//
	// 	static const Vector3 UnitZ;
	//
	// 	static const Vector3 Up;
	//
	// 	static const Vector3 Down;
	//
	// 	static const Vector3 Right;
	//
	// 	static const Vector3 Left;
	//
	// 	static const Vector3 Forward;
	//
	// 	static const Vector3 Backward;
	//
	// private:
	// 	DirectX::XMFLOAT3 m_Data;
	// };
	//
	// // Vector3 operator+(const Vector3& vector1,
	// //                   const Vector3& vector2) noexcept;
	// //
	// // Vector3 operator-(const Vector3& vector1,
	// //                   const Vector3& vector2) noexcept;
	// //
	// // Vector3 operator*(const Vector3& vector,
	// //                   float scalar) noexcept;
	// //
	// // Vector3 operator/(const Vector3& vector,
	// //                   float scalar) noexcept;
	//
	// // Not sure yet
	// // class Quaternion;
	//
	// class Matrix4x4
	// {
	// public:
	// 	Matrix4x4() noexcept :
	// 		m_Data(1.f, 0, 0, 0,
	// 		       0, 1.f, 0, 0,
	// 		       0, 0, 1.f, 0,
	// 		       0, 0, 0, 1.f)
	// 	{
	// 	}
	//
	// 	constexpr Matrix4x4(float m00,
	// 	                    float m01,
	// 	                    float m02,
	// 	                    float m03,
	// 	                    float m10,
	// 	                    float m11,
	// 	                    float m12,
	// 	                    float m13,
	// 	                    float m20,
	// 	                    float m21,
	// 	                    float m22,
	// 	                    float m23,
	// 	                    float m30,
	// 	                    float m31,
	// 	                    float m32,
	// 	                    float m33) noexcept :
	// 		m_Data(m00, m01, m02, m03,
	// 		       m10, m11, m12, m13,
	// 		       m20, m21, m22, m23,
	// 		       m30, m31, m32, m33)
	// 	{
	// 	}
	//
	// 	explicit Matrix4x4(const Vector3& r0,
	// 	                   const Vector3& r1,
	// 	                   const Vector3& r2) noexcept :
	// 		m_Data(r0.X(), r0.Y(), r0.Z(), 0,
	// 		       r1.X(), r1.Y(), r1.Z(), 0,
	// 		       r2.X(), r2.Y(), r2.Z(), 0,
	// 		       0, 0, 0, 1.f)
	// 	{
	// 	}
	//
	// 	explicit Matrix4x4(const DirectX::XMFLOAT4X4& M) noexcept
	// 	{
	// 		memcpy(&m_Data, &M, sizeof(DirectX::XMFLOAT4X4));
	// 	}
	//
	// 	Matrix4x4(const Matrix4x4&) = default;
	//
	// 	Matrix4x4& operator=(const Matrix4x4&) = default;
	//
	// 	Matrix4x4(Matrix4x4&&) = default;
	//
	// 	Matrix4x4& operator=(Matrix4x4&&) = default;
	//
	// 	operator DirectX::XMMATRIX() const noexcept
	// 	{
	// 		return XMLoadFloat4x4(&m_Data);
	// 	}
	//
	// 	// Comparison operators
	// 	bool operator ==(const Matrix4x4& M) const noexcept;
	//
	// 	bool operator !=(const Matrix4x4& M) const noexcept;
	//
	// 	// Assignment operators
	// 	Matrix4x4& operator+=(const Matrix4x4& M) noexcept;
	//
	// 	Matrix4x4& operator-=(const Matrix4x4& M) noexcept;
	//
	// 	Matrix4x4& operator*=(const Matrix4x4& M) noexcept;
	//
	// 	Matrix4x4& operator*=(float S) noexcept;
	//
	// 	Matrix4x4& operator/=(float S) noexcept;
	// 	
	// 	// Element-wise divide
	// 	Matrix4x4& operator/=(const Matrix4x4& M) noexcept;
	//
	//
	// 	// Unary operators
	// 	Matrix4x4 operator+() const noexcept
	// 	{
	// 		return *this;
	// 	}
	//
	// 	Matrix4x4 operator-() const noexcept;
	//
	// 	void Translation(const Vector3& v) noexcept
	// 	{
	// 		m_Data._41 = v.X();
	// 		m_Data._42 = v.Y();
	// 		m_Data._43 = v.Z();
	// 	}
	//
	// 	Matrix4x4 Transpose() const noexcept;
	//
	// 	void Transpose(Matrix4x4& result) const noexcept;
	//
	// 	float Determinant() const noexcept;
	//
	// 	// Computes rotation about y-axis (y), then x-axis (x), then z-axis (z)
	// 	Vector3 ToEuler() const noexcept;
	//
	// 	// Static functions
	// 	static Matrix4x4 CreateTranslation(const Vector3& position) noexcept;
	//
	// 	static Matrix4x4 CreateTranslation(float x,
	// 	                                   float y,
	// 	                                   float z) noexcept;
	//
	// 	static Matrix4x4 CreateScale(const Vector3& scales) noexcept;
	//
	// 	static Matrix4x4 CreateScale(float xs,
	// 	                             float ys,
	// 	                             float zs) noexcept;
	//
	// 	static Matrix4x4 CreateScale(float scale) noexcept;
	//
	// 	static Matrix4x4 CreateRotationX(float radians) noexcept;
	//
	// 	static Matrix4x4 CreateRotationY(float radians) noexcept;
	//
	// 	static Matrix4x4 CreateRotationZ(float radians) noexcept;
	//
	// 	static Matrix4x4 CreatePerspectiveFieldOfView(float fov,
	// 	                                              float aspectRatio,
	// 	                                              float nearPlane,
	// 	                                              float farPlane) noexcept;
	//
	// 	static Matrix4x4 CreatePerspective(float width,
	// 	                                   float height,
	// 	                                   float nearPlane,
	// 	                                   float farPlane) noexcept;
	//
	// 	static Matrix4x4 CreatePerspectiveOffCenter(float left,
	// 	                                            float right,
	// 	                                            float bottom,
	// 	                                            float top,
	// 	                                            float nearPlane,
	// 	                                            float farPlane) noexcept;
	//
	// 	static Matrix4x4 CreateOrthographic(float width,
	// 	                                    float height,
	// 	                                    float zNearPlane,
	// 	                                    float zFarPlane) noexcept;
	//
	// 	static Matrix4x4 CreateOrthographicOffCenter(float left,
	// 	                                             float right,
	// 	                                             float bottom,
	// 	                                             float top,
	// 	                                             float zNearPlane,
	// 	                                             float zFarPlane) noexcept;
	//
	// 	// Rotates about y-axis (yaw), then x-axis (pitch), then z-axis (roll)
	// 	static Matrix4x4 CreateFromYawPitchRoll(float yaw,
	// 	                                        float pitch,
	// 	                                        float roll) noexcept;
	//
	// 	// Rotates about y-axis (angles.y), then x-axis (angles.x), then z-axis (angles.z)
	// 	static Matrix4x4 CreateFromYawPitchRoll(const Vector3& angles) noexcept;
	//
	// 	// Constants
	// 	static const Matrix4x4 Identity;
	//
	// private:
	// 	DirectX::XMFLOAT4X4 m_Data;
	// };
	//
	// // // Binary operators
	// // Matrix4x4 operator+(const Matrix4x4& M1,
	// //                     const Matrix4x4& M2) noexcept;
	// //
	// // Matrix4x4 operator-(const Matrix4x4& M1,
	// //                     const Matrix4x4& M2) noexcept;
	// //
	// // Matrix4x4 operator*(const Matrix4x4& M1,
	// //                     const Matrix4x4& M2) noexcept;
	// //
	// // Matrix4x4 operator*(const Matrix4x4& M,
	// //                     float S) noexcept;
	// //
	// // Matrix4x4 operator/(const Matrix4x4& M,
	// //                     float S) noexcept;
	// //
	// // Matrix4x4 operator/(const Matrix4x4& M1,
	// //                     const Matrix4x4& M2) noexcept;
	// //
	// // // Element-wise divide
	// // Matrix4x4 operator*(float S,
	// //                     const Matrix4x4& M) noexcept;
	//
	// class Color final
	// {
	// public:
	// 	explicit Color() noexcept;
	//
	// 	constexpr Color(const float red,
	// 	                const float green,
	// 	                const float blue) noexcept :
	// 		m_Data{red, green, blue, 1.0f}
	// 	{
	// 	}
	//
	// 	constexpr Color(const float red,
	// 	                const float green,
	// 	                const float blue,
	// 	                const float alpha) noexcept :
	// 		m_Data{red, green, blue, alpha}
	// 	{
	// 	};
	//
	// 	Color(const Color&) = default;
	//
	// 	Color& operator=(const Color&) = default;
	//
	// 	Color(Color&&) = default;
	//
	// 	Color& operator=(Color&&) = default;
	//
	// 	operator DirectX::XMVECTOR() const noexcept;
	//
	// 	bool operator ==(const Color& color) const noexcept;
	//
	// 	bool operator !=(const Color& color) const noexcept;
	//
	// 	Color& operator+=(const Color& color) noexcept;
	//
	// 	Color& operator-=(const Color& color) noexcept;
	//
	// 	Color& operator*=(const Color& color) noexcept;
	//
	// 	Color& operator*=(float scalar) noexcept;
	//
	// 	Color& operator/=(const Color& color) noexcept;
	//
	// 	Color operator+() const noexcept;
	//
	// 	Color operator-() const noexcept;
	//
	// 	operator const float*() const noexcept;
	//
	// 	float Red() const noexcept;
	//
	// 	void Red(float red) noexcept;
	//
	// 	float Green() const noexcept;
	//
	// 	void Green(float green) noexcept;
	//
	// 	float Blue() const noexcept;
	//
	// 	void Blue(float blue) noexcept;
	//
	// 	float Alpha() const noexcept;
	//
	// 	void Alpha(float alpha) noexcept;
	//
	// 	static Color Lerp(const Color& color1,
	// 	                  const Color& color2,
	// 	                  float ratio) noexcept;
	//
	// private:
	// 	DirectX::XMFLOAT4 m_Data;
	// };
	//
	// // Color operator+(const Color& color1,
	// //                 const Color& color2) noexcept;
	// //
	// // Color operator-(const Color& color1,
	// //                 const Color& color2) noexcept;
	// //
	// // Color operator*(const Color& color1,
	// //                 const Color& color2) noexcept;
	// //
	// // Color operator*(const Color& color,
	// //                 float scalar) noexcept;
	// //
	// // Color operator/(const Color& color1,
	// //                 const Color& color2) noexcept;
	//
	// class Viewport final
	// {
	// public:
	// 	Viewport() noexcept :
	// 		m_X(0.f),
	// 		m_Y(0.f),
	// 		m_Width(0.f),
	// 		m_Height(0.f),
	// 		m_MinDepth(0.f),
	// 		m_MaxDepth(1.f)
	// 	{
	// 	}
	//
	// 	constexpr Viewport(const float x,
	// 	                   const float y,
	// 	                   const float width,
	// 	                   const float height,
	// 	                   const float minDepth = 0.f,
	// 	                   const float maxDepth = 1.f) noexcept :
	// 		m_X(x),
	// 		m_Y(y),
	// 		m_Width(width),
	// 		m_Height(height),
	// 		m_MinDepth(minDepth),
	// 		m_MaxDepth(maxDepth)
	// 	{
	// 	}
	//
	// 	Viewport(const Viewport&) = default;
	//
	// 	Viewport& operator=(const Viewport&) = default;
	//
	// 	Viewport(Viewport&&) = default;
	//
	// 	Viewport& operator=(Viewport&&) = default;
	//
	// 	// Not sure yet
	// 	// float AspectRatio() const noexcept;
	// 	//
	// 	// Vector3 Project(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world) const noexcept;
	// 	// void Project(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world, Vector3& result) const noexcept;
	// 	//
	// 	// Vector3 Unproject(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world) const noexcept;
	// 	// void Unproject(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world, Vector3& result) const noexcept;
	//
	// private:
	// 	float m_X;
	//
	// 	float m_Y;
	//
	// 	float m_Width;
	//
	// 	float m_Height;
	//
	// 	float m_MinDepth;
	//
	// 	float m_MaxDepth;
	// };
}
