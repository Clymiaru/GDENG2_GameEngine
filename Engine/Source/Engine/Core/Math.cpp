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

	const Matrix4x4 Matrix4x4::Identity = {
		1.f,
		0.f,
		0.f,
		0.f,
		0.f,
		1.f,
		0.f,
		0.f,
		0.f,
		0.f,
		1.f,
		0.f,
		0.f,
		0.f,
		0.f,
		1.f
	};

	inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& M) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._41), x4);
		return *this;
	}

	inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& M) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._41), x4);
		return *this;
	}

	inline Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& M) noexcept
	{
		using namespace DirectX;
		const XMMATRIX M1 = XMLoadFloat4x4(&m_Data);
		const XMMATRIX M2 = XMLoadFloat4x4(&M.m_Data);
		const XMMATRIX X  = XMMatrixMultiply(M1, M2);
		XMStoreFloat4x4(&m_Data, X);
		return *this;
	}

	inline Matrix4x4& Matrix4x4::operator*=(float S) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._41), x4);
		return *this;
	}

	inline Matrix4x4& Matrix4x4::operator/=(float S) noexcept
	{
		using namespace DirectX;
		assert(S != 0.f);
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		const float rs = 1.f / S;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._41), x4);
		return *this;
	}

	inline Matrix4x4& Matrix4x4::operator/=(const Matrix4x4& M) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&m_Data._41), x4);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	inline Matrix4x4 Matrix4x4::operator-() const noexcept
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._11));
		XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._21));
		XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._31));
		XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m_Data._41));

		v1 = XMVectorNegate(v1);
		v2 = XMVectorNegate(v2);
		v3 = XMVectorNegate(v3);
		v4 = XMVectorNegate(v4);

		Matrix4x4 R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R.m_Data._11), v1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R.m_Data._21), v2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R.m_Data._31), v3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R.m_Data._41), v4);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	// inline Matrix4x4 operator+(const Matrix4x4& M1,
	//                            const Matrix4x4& M2) noexcept
	// {
	// 	using namespace DirectX;
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));
	//
	// 	const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	// 	const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	// 	const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	// 	const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));
	//
	// 	x1 = XMVectorAdd(x1, y1);
	// 	x2 = XMVectorAdd(x2, y2);
	// 	x3 = XMVectorAdd(x3, y3);
	// 	x4 = XMVectorAdd(x4, y4);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator-(const Matrix4x4& M1,
	//                            const Matrix4x4& M2) noexcept
	// {
	// 	using namespace DirectX;
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));
	//
	// 	const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	// 	const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	// 	const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	// 	const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));
	//
	// 	x1 = XMVectorSubtract(x1, y1);
	// 	x2 = XMVectorSubtract(x2, y2);
	// 	x3 = XMVectorSubtract(x3, y3);
	// 	x4 = XMVectorSubtract(x4, y4);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator*(const Matrix4x4& M1,
	//                            const Matrix4x4& M2) noexcept
	// {
	// 	using namespace DirectX;
	// 	const XMMATRIX m1 = XMLoadFloat4x4(&M1);
	// 	const XMMATRIX m2 = XMLoadFloat4x4(&M2);
	// 	const XMMATRIX X  = XMMatrixMultiply(m1, m2);
	//
	// 	Matrix R;
	// 	XMStoreFloat4x4(&R, X);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator*(const Matrix4x4& M,
	//                            float S) noexcept
	// {
	// 	using namespace DirectX;
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));
	//
	// 	x1 = XMVectorScale(x1, S);
	// 	x2 = XMVectorScale(x2, S);
	// 	x3 = XMVectorScale(x3, S);
	// 	x4 = XMVectorScale(x4, S);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator/(const Matrix4x4& M,
	//                            float S) noexcept
	// {
	// 	using namespace DirectX;
	// 	assert(S != 0.f);
	//
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));
	//
	// 	const float rs = 1.f / S;
	//
	// 	x1 = XMVectorScale(x1, rs);
	// 	x2 = XMVectorScale(x2, rs);
	// 	x3 = XMVectorScale(x3, rs);
	// 	x4 = XMVectorScale(x4, rs);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator/(const Matrix4x4& M1,
	//                            const Matrix4x4& M2) noexcept
	// {
	// 	using namespace DirectX;
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));
	//
	// 	const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
	// 	const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
	// 	const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
	// 	const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));
	//
	// 	x1 = XMVectorDivide(x1, y1);
	// 	x2 = XMVectorDivide(x2, y2);
	// 	x3 = XMVectorDivide(x3, y3);
	// 	x4 = XMVectorDivide(x4, y4);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }
	//
	// inline Matrix4x4 operator*(float S,
	//                            const Matrix4x4& M) noexcept
	// {
	// 	using namespace DirectX;
	//
	// 	XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M.m_Data._11));
	// 	XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
	// 	XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
	// 	XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));
	//
	// 	x1 = XMVectorScale(x1, S);
	// 	x2 = XMVectorScale(x2, S);
	// 	x3 = XMVectorScale(x3, S);
	// 	x4 = XMVectorScale(x4, S);
	//
	// 	Matrix4x4 R;
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R.m_Data._11), x1);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
	// 	XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
	// 	return R;
	// }

	//------------------------------------------------------------------------------
	// Matrix operations
	//------------------------------------------------------------------------------
	inline Matrix4x4 Matrix4x4::Transpose() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX M = XMLoadFloat4x4(&m_Data);
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixTranspose(M));
		return R;
	}

	inline void Matrix4x4::Transpose(Matrix4x4& result) const noexcept
	{
		using namespace DirectX;
		const XMMATRIX M = XMLoadFloat4x4(&m_Data);
		XMStoreFloat4x4(&result.m_Data, XMMatrixTranspose(M));
	}

	inline float Matrix4x4::Determinant() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX M = XMLoadFloat4x4(&m_Data);
		return XMVectorGetX(XMMatrixDeterminant(M));
	}

	inline Vector3 Matrix4x4::ToEuler() const noexcept
	{
		const float cy = sqrtf(m_Data._33 * m_Data._33 + m_Data._31 * m_Data._31);
		const float cx = atan2f(-m_Data._32, cy);
		if (cy > 16.f * FLT_EPSILON)
		{
			return Vector3(cx, atan2f(m_Data._31, m_Data._33), atan2f(m_Data._12, m_Data._22));
		}
		else
		{
			return Vector3(cx, 0.f, atan2f(-m_Data._21, m_Data._11));
		}
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	inline Matrix4x4 Matrix4x4::CreateTranslation(const Vector3& position) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixTranslation(position.X(), position.Y(), position.Z()));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateTranslation(float x,
	                                              float y,
	                                              float z) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixTranslation(x, y, z));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateScale(const Vector3& scales) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixScaling(scales.X(), scales.Y(), scales.Z()));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateScale(float xs,
	                                        float ys,
	                                        float zs) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixScaling(xs, ys, zs));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateScale(float scale) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixScaling(scale, scale, scale));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateRotationX(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixRotationX(radians));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateRotationY(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixRotationY(radians));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateRotationZ(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixRotationZ(radians));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreatePerspectiveFieldOfView(float fov,
	                                                         float aspectRatio,
	                                                         float nearPlane,
	                                                         float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixPerspectiveFovRH(fov, aspectRatio, nearPlane, farPlane));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreatePerspective(float width,
	                                              float height,
	                                              float nearPlane,
	                                              float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixPerspectiveRH(width, height, nearPlane, farPlane));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreatePerspectiveOffCenter(float left,
	                                                       float right,
	                                                       float bottom,
	                                                       float top,
	                                                       float nearPlane,
	                                                       float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixPerspectiveOffCenterRH(left, right, bottom, top, nearPlane, farPlane));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateOrthographic(float width,
	                                               float height,
	                                               float zNearPlane,
	                                               float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixOrthographicRH(width, height, zNearPlane, zFarPlane));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateOrthographicOffCenter(float left,
	                                                        float right,
	                                                        float bottom,
	                                                        float top,
	                                                        float zNearPlane,
	                                                        float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixOrthographicOffCenterRH(left, right, bottom, top, zNearPlane, zFarPlane));
		return R;
	}


	inline Matrix4x4 Matrix4x4::CreateFromYawPitchRoll(float yaw,
	                                                   float pitch,
	                                                   float roll) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	inline Matrix4x4 Matrix4x4::CreateFromYawPitchRoll(const Vector3& angles) noexcept
	{
		using namespace DirectX;
		Matrix4x4 R;
		XMStoreFloat4x4(&R.m_Data, XMMatrixRotationRollPitchYawFromVector(angles));
		return R;
	}

	const Vector2 Vector2::Zero = Vector2{ 0.f, 0.f };
	const Vector2 Vector2::One = Vector2{ 1.f, 1.f };
	const Vector2 Vector2::UnitX = Vector2{ 1.f, 0.f };
	const Vector2 Vector2::UnitY = Vector2{ 0.f, 1.f };

	const Vector3 Vector3::Zero = Vector3{ 0.f, 0.f, 0.f };
	const Vector3 Vector3::One = Vector3{ 1.f, 1.f, 1.f };
	const Vector3 Vector3::UnitX = Vector3{ 1.f, 0.f, 0.f };
	const Vector3 Vector3::UnitY = Vector3{ 0.f, 1.f, 0.f };
	const Vector3 Vector3::UnitZ = Vector3{ 0.f, 0.f, 1.f };
	const Vector3 Vector3::Up = Vector3{ 0.f, 1.f, 0.f };
	const Vector3 Vector3::Down = Vector3{ 0.f, -1.f, 0.f };
	const Vector3 Vector3::Right = Vector3{ 1.f, 0.f, 0.f };
	const Vector3 Vector3::Left = Vector3{ -1.f, 0.f, 0.f };
	const Vector3 Vector3::Forward = Vector3{ 0.f, 0.f, -1.f };
	const Vector3 Vector3::Backward = Vector3{ 0.f, 0.f, 1.f };
}
