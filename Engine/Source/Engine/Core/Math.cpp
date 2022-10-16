#include "pch.h"
#include "Math.h"

#include "Debug.h"

namespace Engine
{
	//----------VECTOR2
	Vector2::Vector2() noexcept :
		m_Data{0.0f, 0.0f}
	{
	}

	constexpr Vector2::Vector2(const float x,
	                           const float y) noexcept :
		m_Data{x, y}
	{
	}

	Vector2::operator DirectX::XMVECTOR() const noexcept
	{
		return XMLoadFloat2(&m_Data);
	}

	bool Vector2::operator==(const Vector2& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat2(&m_Data);
		const XMVECTOR v2 = XMLoadFloat2(&other.m_Data);
		return XMVector2Equal(v1, v2);
	}

	bool Vector2::operator!=(const Vector2& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat2(&m_Data);
		const XMVECTOR v2 = XMLoadFloat2(&other.m_Data);
		return XMVector2NotEqual(v1, v2);
	}

	Vector2& Vector2::operator+=(const Vector2& other) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1  = XMLoadFloat2(&m_Data);
		const XMVECTOR v2  = XMLoadFloat2(&other.m_Data);
		const XMVECTOR sum = XMVectorAdd(v1, v2);
		XMStoreFloat2(&m_Data, sum);
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadFloat2(&m_Data);
		const XMVECTOR v2         = XMLoadFloat2(&other.m_Data);
		const XMVECTOR difference = XMVectorSubtract(v1, v2);
		XMStoreFloat2(&m_Data, difference);
		return *this;
	}

	Vector2& Vector2::operator*=(const float scalar) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(&m_Data);
		const XMVECTOR scaled = XMVectorScale(v1, scalar);
		XMStoreFloat2(&m_Data, scaled);
		return *this;
	}

	Vector2& Vector2::operator/=(const float scalar) noexcept
	{
		using namespace DirectX;
		ENGINE_ASSERT(scalar != 0.0f, "Cannot divide vector by 0.");
		const XMVECTOR v1     = XMLoadFloat2(&m_Data);
		const XMVECTOR scaled = XMVectorScale(v1, 1.0f / scalar);
		XMStoreFloat2(&m_Data, scaled);
		return *this;
	}

	Vector2 Vector2::operator+() const noexcept
	{
		return *this;
	}

	Vector2 Vector2::operator-() const noexcept
	{
		return Vector2(-m_Data.x, -m_Data.y);
	}

	float Vector2::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat2(&m_Data);
		const XMVECTOR length = XMVector2Length(v1);
		return XMVectorGetX(length);
	}

	float Vector2::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1       = XMLoadFloat2(&m_Data);
		const XMVECTOR lengthSq = XMVector2LengthSq(v1);
		return XMVectorGetX(lengthSq);
	}

	float Vector2::Dot(const Vector2& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1  = XMLoadFloat2(&m_Data);
		const XMVECTOR v2  = XMLoadFloat2(&other.m_Data);
		const XMVECTOR dot = XMVector2Dot(v1, v2);
		return XMVectorGetX(dot);
	}

	Vector2 Vector2::Cross(const Vector2& other) const noexcept
	{
		using namespace DirectX;
		Vector2 result       = Vector2();
		const XMVECTOR v1    = XMLoadFloat2(&m_Data);
		const XMVECTOR v2    = XMLoadFloat2(&other.m_Data);
		const XMVECTOR cross = XMVector2Cross(v1, v2);
		XMStoreFloat2(&result.m_Data, cross);
		return result;
	}

	void Vector2::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1        = XMLoadFloat2(&m_Data);
		const XMVECTOR normalize = XMVector2Normalize(v1);
		XMStoreFloat2(&m_Data, normalize);
	}

	Vector2 Vector2::Normalize() const noexcept
	{
		using namespace DirectX;
		Vector2 result           = Vector2();
		const XMVECTOR v1        = XMLoadFloat2(&m_Data);
		const XMVECTOR normalize = XMVector2Normalize(v1);
		XMStoreFloat2(&result.m_Data, normalize);
		return result;
	}

	float Vector2::X() const noexcept
	{
		return m_Data.x;
	}

	void Vector2::X(const float x) noexcept
	{
		m_Data.x = x;
	}

	float Vector2::Y() const noexcept
	{
		return m_Data.y;
	}

	void Vector2::Y(const float y) noexcept
	{
		m_Data.y = y;
	}

	// Vector2 operator+(const Vector2& vector1,
	//                   const Vector2& vector2) noexcept
	// {
	// 	Vector2 result(vector1);
	// 	return result += vector2;
	// }
	//
	// Vector2 operator-(const Vector2& vector1,
	//                   const Vector2& vector2) noexcept
	// {
	// 	Vector2 result(vector1);
	// 	return result -= vector2;
	// }
	//
	// Vector2 operator*(const Vector2& vector,
	//                   const float scalar) noexcept
	// {
	// 	Vector2 result(vector);
	// 	return result *= scalar;
	// }
	//
	// Vector2 operator/(const Vector2& vector,
	//                   const float scalar) noexcept
	// {
	// 	Vector2 vector1(vector);
	// 	return vector1 /= scalar;
	// }

	//----------VECTOR3
	// Vector3::Vector3() noexcept:
	// 	XMFLOAT3{0.0f, 0.0f, 0.0f}
	// {
	// }
	//
	// constexpr Vector3::Vector3(const float x,
	//                            const float y,
	//                            const float z) noexcept:
	// 	XMFLOAT3{x, y, z}
	// {
	// }
	//
	// Vector3::operator DirectX::XMVECTOR() const noexcept
	// {
	// 	return XMLoadFloat3(this);
	// }
	//
	// bool Vector3::operator==(const Vector3& other) const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1 = XMLoadFloat3(this);
	// 	const XMVECTOR v2 = XMLoadFloat3(&other);
	// 	return XMVector3Equal(v1, v2);
	// }
	//
	// bool Vector3::operator!=(const Vector3& other) const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1 = XMLoadFloat3(this);
	// 	const XMVECTOR v2 = XMLoadFloat3(&other);
	// 	return XMVector3NotEqual(v1, v2);
	// }
	//
	// Vector3& Vector3::operator+=(const Vector3& other) noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadFloat3(this);
	// 	const XMVECTOR v2  = XMLoadFloat3(&other);
	// 	const XMVECTOR sum = XMVectorAdd(v1, v2);
	// 	XMStoreFloat3(this, sum);
	// 	return *this;
	// }
	//
	// Vector3& Vector3::operator-=(const Vector3& other) noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1         = XMLoadFloat3(this);
	// 	const XMVECTOR v2         = XMLoadFloat3(&other);
	// 	const XMVECTOR difference = XMVectorSubtract(v1, v2);
	// 	XMStoreFloat3(this, difference);
	// 	return *this;
	// }
	//
	// Vector3& Vector3::operator*=(float scalar) noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat3(this);
	// 	const XMVECTOR scaled = XMVectorScale(v1, scalar);
	// 	XMStoreFloat3(this, scaled);
	// 	return *this;
	// }
	//
	// Vector3& Vector3::operator/=(float scalar) noexcept
	// {
	// 	using namespace DirectX;
	// 	ENGINE_ASSERT(scalar != 0.0f, "Cannot divide Vector3 by 0.");
	// 	const XMVECTOR v1     = XMLoadFloat3(this);
	// 	const XMVECTOR scaled = XMVectorScale(v1, 1.0f / scalar);
	// 	XMStoreFloat3(this, scaled);
	// 	return *this;
	// }
	//
	// Vector3 Vector3::operator+() const noexcept
	// {
	// 	return *this;
	// }
	//
	// Vector3 Vector3::operator-() const noexcept
	// {
	// 	return Vector3(-x, -y, -z);
	// }
	//
	// float Vector3::Length() const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1     = XMLoadFloat3(this);
	// 	const XMVECTOR length = XMVector3Length(v1);
	// 	return XMVectorGetX(length);
	// }
	//
	// float Vector3::LengthSquared() const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1       = XMLoadFloat3(this);
	// 	const XMVECTOR lengthSq = XMVector3LengthSq(v1);
	// 	return XMVectorGetX(lengthSq);
	// }
	//
	// float Vector3::Dot(const Vector3& other) const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1  = XMLoadFloat3(this);
	// 	const XMVECTOR v2  = XMLoadFloat3(&other);
	// 	const XMVECTOR dot = XMVector3Dot(v1, v2);
	// 	return XMVectorGetX(dot);
	// }
	//
	// Vector3 Vector3::Cross(const Vector3& other) const noexcept
	// {
	// 	using namespace DirectX;
	// 	Vector3 result       = Vector3();
	// 	const XMVECTOR v1    = XMLoadFloat3(this);
	// 	const XMVECTOR v2    = XMLoadFloat3(&other);
	// 	const XMVECTOR cross = XMVector3Cross(v1, v2);
	// 	XMStoreFloat3(&result, cross);
	// 	return result;
	// }
	//
	// void Vector3::Normalize() noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1 = XMLoadFloat3(this);
	// 	const XMVECTOR X  = XMVector3Normalize(v1);
	// 	XMStoreFloat3(this, X);
	// }
	//
	// Vector3 Vector3::Normalize() const noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMVECTOR v1 = XMLoadFloat3(this);
	// 	const XMVECTOR X  = XMVector3Normalize(v1);
	//
	// 	Vector3 result = Vector3();
	// 	XMStoreFloat3(&result, X);
	// 	return result;
	// }
	
	Vector3::Vector3() noexcept:
		m_Data{0.0f, 0.0f, 0.0f}
	{
	}
	
	constexpr Vector3::Vector3(const float x,
	                           const float y,
	                           const float z) noexcept:
		m_Data{x, y, z}
	{
	}
	
	Vector3::operator DirectX::XMVECTOR() const noexcept
	{
		return XMLoadFloat3(&m_Data);
	}
	
	bool Vector3::operator==(const Vector3& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(&m_Data);
		const XMVECTOR v2 = XMLoadFloat3(&other.m_Data);
		return XMVector3Equal(v1, v2);
	}
	
	bool Vector3::operator!=(const Vector3& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(&m_Data);
		const XMVECTOR v2 = XMLoadFloat3(&other.m_Data);
		return XMVector3NotEqual(v1, v2);
	}
	
	Vector3& Vector3::operator+=(const Vector3& other) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1  = XMLoadFloat3(&m_Data);
		const XMVECTOR v2  = XMLoadFloat3(&other.m_Data);
		const XMVECTOR sum = XMVectorAdd(v1, v2);
		XMStoreFloat3(&m_Data, sum);
		return *this;
	}
	
	Vector3& Vector3::operator-=(const Vector3& other) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1         = XMLoadFloat3(&m_Data);
		const XMVECTOR v2         = XMLoadFloat3(&other.m_Data);
		const XMVECTOR difference = XMVectorSubtract(v1, v2);
		XMStoreFloat3(&m_Data, difference);
		return *this;
	}
	
	Vector3& Vector3::operator*=(float scalar) noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(&m_Data);
		const XMVECTOR scaled = XMVectorScale(v1, scalar);
		XMStoreFloat3(&m_Data, scaled);
		return *this;
	}
	
	Vector3& Vector3::operator/=(float scalar) noexcept
	{
		using namespace DirectX;
		ENGINE_ASSERT(scalar != 0.0f, "Cannot divide Vector3 by 0.");
		const XMVECTOR v1     = XMLoadFloat3(&m_Data);
		const XMVECTOR scaled = XMVectorScale(v1, 1.0f / scalar);
		XMStoreFloat3(&m_Data, scaled);
		return *this;
	}
	
	Vector3 Vector3::operator+() const noexcept
	{
		return *this;
	}
	
	Vector3 Vector3::operator-() const noexcept
	{
		return Vector3(-m_Data.x, -m_Data.y, -m_Data.z);
	}
	
	float Vector3::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1     = XMLoadFloat3(&m_Data);
		const XMVECTOR length = XMVector3Length(v1);
		return XMVectorGetX(length);
	}
	
	float Vector3::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1       = XMLoadFloat3(&m_Data);
		const XMVECTOR lengthSq = XMVector3LengthSq(v1);
		return XMVectorGetX(lengthSq);
	}
	
	float Vector3::Dot(const Vector3& other) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1  = XMLoadFloat3(&m_Data);
		const XMVECTOR v2  = XMLoadFloat3(&other.m_Data);
		const XMVECTOR dot = XMVector3Dot(v1, v2);
		return XMVectorGetX(dot);
	}
	
	Vector3 Vector3::Cross(const Vector3& other) const noexcept
	{
		using namespace DirectX;
		Vector3 result       = Vector3();
		const XMVECTOR v1    = XMLoadFloat3(&m_Data);
		const XMVECTOR v2    = XMLoadFloat3(&other.m_Data);
		const XMVECTOR cross = XMVector3Cross(v1, v2);
		XMStoreFloat3(&result.m_Data, cross);
		return result;
	}
	
	void Vector3::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(&m_Data);
		const XMVECTOR X  = XMVector3Normalize(v1);
		XMStoreFloat3(&m_Data, X);
	}
	
	Vector3 Vector3::Normalize() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR v1 = XMLoadFloat3(&m_Data);
		const XMVECTOR X  = XMVector3Normalize(v1);
	
		Vector3 result = Vector3();
		XMStoreFloat3(&result.m_Data, X);
		return result;
	}

	float Vector3::X() const noexcept
	{
		return m_Data.x;
	}

	void Vector3::X(const float x) noexcept
	{
		m_Data.x = x;
	}

	float Vector3::Y() const noexcept
	{
		return m_Data.y;
	}

	void Vector3::Y(const float y) noexcept
	{
		m_Data.y = y;
	}

	float Vector3::Z() const noexcept
	{
		return m_Data.z;
	}

	void Vector3::Z(const float z) noexcept
	{
		m_Data.z = z;
	}

	// Vector3 operator+(const Vector3& vector1,
	//                   const Vector3& vector2) noexcept
	// {
	// 	Vector3 result(vector1);
	// 	return result += vector2;
	// }
	//
	// Vector3 operator-(const Vector3& vector1,
	//                   const Vector3& vector2) noexcept
	// {
	// 	Vector3 result(vector1);
	// 	return result -= vector2;
	// }
	//
	// Vector3 operator*(const Vector3& vector,
	//                   float scalar) noexcept
	// {
	// 	Vector3 result(vector);
	// 	return result *= scalar;
	// }
	//
	// Vector3 operator/(const Vector3& vector,
	//                   float scalar) noexcept
	// {
	// 	Vector3 result(vector);
	// 	return result /= scalar;
	// }

	//----------COLOR
	Color::Color() noexcept :
		m_Data{1.0f, 1.0f, 1.0f, 1.0f}
	{
	}
	
	Color::operator DirectX::XMVECTOR() const noexcept
	{
		return XMLoadFloat4(&m_Data);
	}
	
	bool Color::operator==(const Color& color) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		return XMColorEqual(c1, c2);
	}
	
	bool Color::operator!=(const Color& color) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		return XMColorNotEqual(c1, c2);
	}
	
	Color& Color::operator+=(const Color& color) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		XMStoreFloat4(&m_Data, XMVectorAdd(c1, c2));
		return *this;
	}
	
	Color& Color::operator-=(const Color& color) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		XMStoreFloat4(&m_Data, XMVectorSubtract(c1, c2));
		return *this;
	}
	
	Color& Color::operator*=(const Color& color) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		XMStoreFloat4(&m_Data, XMVectorMultiply(c1, c2));
		return *this;
	}
	
	Color& Color::operator*=(float scalar) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&m_Data);
		XMStoreFloat4(&m_Data, XMVectorScale(c, scalar));
		return *this;
	}
	
	Color& Color::operator/=(const Color& color) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c1 = XMLoadFloat4(&m_Data);
		const XMVECTOR c2 = XMLoadFloat4(&color.m_Data);
		XMStoreFloat4(&m_Data, XMVectorDivide(c1, c2));
		return *this;
	}
	
	Color Color::operator+() const noexcept
	{
		return *this;
	}
	
	Color Color::operator-() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR c = XMLoadFloat4(&m_Data);
		Color result;
		XMStoreFloat4(&result.m_Data, XMVectorNegate(c));
		return result;
	}
	
	Color::operator const float*() const noexcept
	{
		return reinterpret_cast<const float*>(&m_Data);
	}
	
	float Color::Red() const noexcept
	{
		return m_Data.x;
	}
	
	void Color::Red(const float red) noexcept
	{
		m_Data.x = red;
	}
	
	float Color::Green() const noexcept
	{
		return m_Data.y;
	}
	
	void Color::Green(const float green) noexcept
	{
		m_Data.y = green;
	}
	
	float Color::Blue() const noexcept
	{
		return m_Data.z;
	}
	
	void Color::Blue(const float blue) noexcept
	{
		m_Data.z = blue;
	}
	
	float Color::Alpha() const noexcept
	{
		return m_Data.w;
	}
	
	void Color::Alpha(const float alpha) noexcept
	{
		m_Data.w = alpha;
	}
	
	Color Color::Lerp(const Color& color1,
	                  const Color& color2,
	                  float ratio) noexcept
	{
		using namespace DirectX;
		const XMVECTOR c0 = XMLoadFloat4(&color1.m_Data);
		const XMVECTOR c1 = XMLoadFloat4(&color2.m_Data);
		Color result      = Color();
		XMStoreFloat4(&result.m_Data, XMVectorLerp(c0, c1, ratio));
		return result;
	}

	// Color operator+(const Color& color1,
	//                 const Color& color2) noexcept
	// {
	// 	Color color3(color1);
	// 	return color3 += color2;
	// }
	//
	// Color operator-(const Color& color1,
	//                 const Color& color2) noexcept
	// {
	// 	Color color3(color1);
	// 	return color3 -= color2;
	// }
	//
	// Color operator*(const Color& color1,
	//                 const Color& color2) noexcept
	// {
	// 	Color color3(color1);
	// 	return color3 *= color2;
	// }
	//
	// Color operator*(const Color& color,
	//                 float scalar) noexcept
	// {
	// 	Color color1(color);
	// 	return color1 *= scalar;
	// }
	//
	// Color operator/(const Color& color1,
	//                 const Color& color2) noexcept
	// {
	// 	Color color3(color1);
	// 	return color3 /= color2;
	// }
}
