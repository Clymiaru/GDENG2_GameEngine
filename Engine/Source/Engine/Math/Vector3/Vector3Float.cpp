#include "pch.h"
#include "Vector3Float.h"

namespace Engine
{
	Vector3Float Vector3Float::Zero = Vector3Float(0.0f, 0.0f, 0.0f);
	Vector3Float Vector3Float::One  = Vector3Float(1.0f, 1.0f, 1.0f);

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
	
	Vector3Float Vector3Float::Transform(const Vector3Float& v, const Matrix4& m)
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(&v);
		const XMMATRIX M = XMLoadFloat4x4(&m);
		const XMVECTOR X = XMVector3TransformCoord(v1, M);

		Vector3Float result;
		XMStoreFloat3(&result, X);
		return result;
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

	// std::ostream& operator<<(std::ostream& os, const Vector3Float& v)
	// {
	// 	os << "{" << v.x << ", " << v.y << ", " << v.z << "}";
	// 	return os;
	// }
}