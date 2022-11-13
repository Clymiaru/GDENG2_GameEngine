#pragma once
#include <DirectXMath.h>

#include "Rect.h"

namespace Engine
{
	constexpr float DegreesToRadians(const float degrees)
	{
		using namespace DirectX;
		return XMConvertToRadians(degrees);
	}

	constexpr float RadiansToDegrees(const float radians)
	{
		using namespace DirectX;
		return XMConvertToDegrees(radians);
	}

	constexpr float PI = 3.141592654f;

	//--------------------------------//
	// Vector2                        //
	//--------------------------------//
	struct Vector2Float final : DirectX::XMFLOAT2
	{
		explicit Vector2Float();

		explicit Vector2Float(float x, float y);

		explicit Vector2Float(const XMFLOAT2& v);

		~Vector2Float();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector2Float& v) const;

		[[nodiscard]]
		Vector2Float Cross(const Vector2Float& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector2Float& v1, const Vector2Float& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Float& v1, const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Min(const Vector2Float& v1, const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Max(const Vector2Float& v1, const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Lerp(const Vector2Float& v1, const Vector2Float& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator float*() const;

		bool operator ==(const Vector2Float& v) const;

		bool operator !=(const Vector2Float& v) const;

		Vector2Float& operator+=(const Vector2Float& v);

		Vector2Float& operator-=(const Vector2Float& v);

		Vector2Float& operator*=(const Vector2Float& v);

		Vector2Float& operator*=(float s);

		Vector2Float& operator/=(float s);

		Vector2Float operator+() const;

		Vector2Float operator-() const;

		Vector2Float(const Vector2Float&)                = default;
		Vector2Float& operator=(const Vector2Float&)     = default;
		Vector2Float(Vector2Float&&) noexcept            = default;
		Vector2Float& operator=(Vector2Float&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector2Float& v);

		static Vector2Float Zero;
		static Vector2Float One;
	};

	Vector2Float operator+(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator-(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator*(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator*(const Vector2Float& v, float s);
	Vector2Float operator/(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator/(const Vector2Float& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector2Float& v);

	struct Vector2Int final : DirectX::XMINT2
	{
		explicit Vector2Int();

		explicit Vector2Int(int32_t x, int32_t y);

		explicit Vector2Int(const XMINT2& v);

		~Vector2Int();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector2Int& v) const;

		[[nodiscard]]
		Vector2Int Cross(const Vector2Int& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector2Int& v1, const Vector2Int& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Int& v1, const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Min(const Vector2Int& v1, const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Max(const Vector2Int& v1, const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Lerp(const Vector2Int& v1, const Vector2Int& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator int32_t*() const;

		bool operator ==(const Vector2Int& v) const;

		bool operator !=(const Vector2Int& v) const;

		Vector2Int& operator+=(const Vector2Int& v);

		Vector2Int& operator-=(const Vector2Int& v);

		Vector2Int& operator*=(const Vector2Int& v);

		Vector2Int& operator*=(float s);

		Vector2Int& operator/=(float s);

		Vector2Int operator+() const;

		Vector2Int operator-() const;

		Vector2Int(const Vector2Int&)                = default;
		Vector2Int& operator=(const Vector2Int&)     = default;
		Vector2Int(Vector2Int&&) noexcept            = default;
		Vector2Int& operator=(Vector2Int&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector2Int& v);

		static Vector2Int Zero;
		static Vector2Int One;
	};

	Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator*(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator*(const Vector2Int& v, float s);
	Vector2Int operator/(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator/(const Vector2Int& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector2Int& v);

	struct Vector2Uint final : DirectX::XMUINT2
	{
		explicit Vector2Uint();

		explicit Vector2Uint(uint32_t x, uint32_t y);

		explicit Vector2Uint(const XMUINT2& v);

		~Vector2Uint();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector2Uint& v) const;

		[[nodiscard]]
		Vector2Uint Cross(const Vector2Uint& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector2Uint& v1, const Vector2Uint& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Uint& v1, const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Min(const Vector2Uint& v1, const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Max(const Vector2Uint& v1, const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Lerp(const Vector2Uint& v1, const Vector2Uint& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator uint32_t*() const;

		bool operator ==(const Vector2Uint& v) const;

		bool operator !=(const Vector2Uint& v) const;

		Vector2Uint& operator+=(const Vector2Uint& v);

		Vector2Uint& operator-=(const Vector2Uint& v);

		Vector2Uint& operator*=(const Vector2Uint& v);

		Vector2Uint& operator*=(float s);

		Vector2Uint& operator/=(float s);

		Vector2Uint operator+() const;

		Vector2Uint(const Vector2Uint&)                = default;
		Vector2Uint& operator=(const Vector2Uint&)     = default;
		Vector2Uint(Vector2Uint&&) noexcept            = default;
		Vector2Uint& operator=(Vector2Uint&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector2Uint& v);

		static Vector2Uint Zero;
		static Vector2Uint One;
	};

	Vector2Uint operator+(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator-(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator*(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator*(const Vector2Uint& v, float s);
	Vector2Uint operator/(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator/(const Vector2Uint& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector2Uint& v);

	//--------------------------------//
	// Vector3                        //
	//--------------------------------//
	struct Vector3Float final : DirectX::XMFLOAT3
	{
		explicit Vector3Float();

		explicit Vector3Float(float x, float y, float z);

		explicit Vector3Float(const XMFLOAT3& v);

		~Vector3Float();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector3Float& v) const;

		[[nodiscard]]
		Vector3Float Cross(const Vector3Float& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector3Float& v1, const Vector3Float& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Float& v1, const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Min(const Vector3Float& v1, const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Max(const Vector3Float& v1, const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Lerp(const Vector3Float& v1, const Vector3Float& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator float*() const;

		bool operator ==(const Vector3Float& v) const;

		bool operator !=(const Vector3Float& v) const;

		Vector3Float& operator+=(const Vector3Float& v);

		Vector3Float& operator-=(const Vector3Float& v);

		Vector3Float& operator*=(const Vector3Float& v);

		Vector3Float& operator*=(float s);

		Vector3Float& operator/=(float s);

		Vector3Float operator+() const;

		Vector3Float operator-() const;

		Vector3Float(const Vector3Float&)                = default;
		Vector3Float& operator=(const Vector3Float& v)   = default;
		Vector3Float(Vector3Float&&) noexcept            = default;
		Vector3Float& operator=(Vector3Float&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector3Float& v);

		static Vector3Float Zero;
		static Vector3Float One;
	};

	Vector3Float operator+(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator-(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator*(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator*(const Vector3Float& v, float s);
	Vector3Float operator/(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator/(const Vector3Float& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector3Float& v);

	struct Vector3Int final : DirectX::XMINT3
	{
		explicit Vector3Int();

		explicit Vector3Int(int32_t x, int32_t y, int32_t z);

		explicit Vector3Int(const XMINT3& v);

		~Vector3Int();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector3Int& v) const;

		[[nodiscard]]
		Vector3Int Cross(const Vector3Int& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector3Int& v1, const Vector3Int& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Int& v1, const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Min(const Vector3Int& v1, const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Max(const Vector3Int& v1, const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Lerp(const Vector3Int& v1, const Vector3Int& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator int32_t*() const;

		bool operator ==(const Vector3Int& v) const;

		bool operator !=(const Vector3Int& v) const;

		Vector3Int& operator+=(const Vector3Int& v);

		Vector3Int& operator-=(const Vector3Int& v);

		Vector3Int& operator*=(const Vector3Int& v);

		Vector3Int& operator*=(float s);

		Vector3Int& operator/=(float s);

		Vector3Int operator+() const;

		Vector3Int operator-() const;

		Vector3Int(const Vector3Int&)                = default;
		Vector3Int& operator=(const Vector3Int& v)   = default;
		Vector3Int(Vector3Int&&) noexcept            = default;
		Vector3Int& operator=(Vector3Int&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector3Int& v);

		static Vector3Int Zero;
		static Vector3Int One;
	};

	Vector3Int operator+(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator-(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator*(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator*(const Vector3Int& v, float s);
	Vector3Int operator/(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator/(const Vector3Int& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector3Int& v);

	struct Vector3Uint final : DirectX::XMUINT3
	{
		explicit Vector3Uint();

		explicit Vector3Uint(uint32_t x, uint32_t y, uint32_t z);

		explicit Vector3Uint(const XMUINT3& v);

		~Vector3Uint();

		[[nodiscard]]
		float Length() const;

		[[nodiscard]]
		float LengthSquared() const;

		[[nodiscard]]
		float Dot(const Vector3Uint& v) const;

		[[nodiscard]]
		Vector3Uint Cross(const Vector3Uint& v) const;

		void Normalize();

		[[nodiscard]]
		static float Distance(const Vector3Uint& v1, const Vector3Uint& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Uint& v1, const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Min(const Vector3Uint& v1, const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Max(const Vector3Uint& v1, const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Lerp(const Vector3Uint& v1, const Vector3Uint& v2, float t);

		explicit operator DirectX::XMVECTOR() const;

		explicit operator uint32_t*() const;

		bool operator ==(const Vector3Uint& v) const;

		bool operator !=(const Vector3Uint& v) const;

		Vector3Uint& operator+=(const Vector3Uint& v);

		Vector3Uint& operator-=(const Vector3Uint& v);

		Vector3Uint& operator*=(const Vector3Uint& v);

		Vector3Uint& operator*=(float s);

		Vector3Uint& operator/=(float s);

		Vector3Uint operator+() const;

		Vector3Uint(const Vector3Uint&)                = default;
		Vector3Uint& operator=(const Vector3Uint& v)   = default;
		Vector3Uint(Vector3Uint&&) noexcept            = default;
		Vector3Uint& operator=(Vector3Uint&&) noexcept = default;

		friend std::ostream& operator<<(std::ostream& os, const Vector3Uint& v);

		static Vector3Uint Zero;
		static Vector3Uint One;
	};

	Vector3Uint operator+(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator-(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator*(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator*(const Vector3Uint& v, float s);
	Vector3Uint operator/(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator/(const Vector3Uint& v, float s);
	std::ostream& operator<<(std::ostream& os, const Vector3Uint& v);

	// TODO
	//--------------------------------//
	// Vector4                        //
	//--------------------------------//

	// TODO
	//--------------------------------//
	// Quaternion                     //
	//--------------------------------//

	//--------------------------------//
	// Matrix                         //
	//--------------------------------//
	// 4x4 Matrix (assumes right-handed cooordinates)
	struct Matrix4 final : DirectX::XMFLOAT4X4
	{
		explicit Matrix4();

		explicit Matrix4(const Vector3Float& r0, const Vector3Float& r1, const Vector3Float& r2);

		~Matrix4();

		Matrix4 Transpose() const noexcept;

		//Vector3Float ToEuler() const noexcept;

		float Determinant() const noexcept;

		static Matrix4 CreateTranslation(const Vector3Float& position) noexcept;

		static Matrix4 CreateTranslation(float x, float y, float z) noexcept;

		static Matrix4 CreateScale(const Vector3Float& scales) noexcept;

		static Matrix4 CreateScale(float x, float y, float z) noexcept;

		static Matrix4 CreateScale(float scale) noexcept;

		static Matrix4 CreateRotationX(float radians) noexcept;

		static Matrix4 CreateRotationY(float radians) noexcept;

		static Matrix4 CreateRotationZ(float radians) noexcept;

		static Matrix4 CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane,
		                                            float farPlane) noexcept;

		static Matrix4 CreatePerspective(float width, float height, float nearPlane, float farPlane) noexcept;

		static Matrix4 CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept;

		static Matrix4 CreateLookAt(Vector3Float eye, Vector3Float focus, Vector3Float up);

		explicit operator DirectX::XMMATRIX() const;

		bool operator ==(const Matrix4& m) const noexcept;

		bool operator !=(const Matrix4& m) const noexcept;

		Matrix4& operator+=(const Matrix4& m) noexcept;

		Matrix4& operator-=(const Matrix4& m) noexcept;

		Matrix4& operator*=(const Matrix4& m) noexcept;

		Matrix4& operator*=(float s) noexcept;

		Matrix4& operator/=(float s) noexcept;

		// Element-wise divide
		Matrix4& operator/=(const Matrix4& m) noexcept;

		Matrix4 operator-() const noexcept;

		Matrix4(const Matrix4&)            = default;
		Matrix4& operator=(const Matrix4&) = default;
		Matrix4(Matrix4&&)                 = default;
		Matrix4& operator=(Matrix4&&)      = default;
	};

	Matrix4 operator+(const Matrix4& m1, const Matrix4& m2) noexcept;
	Matrix4 operator-(const Matrix4& m1, const Matrix4& m2) noexcept;
	Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) noexcept;
	Matrix4 operator*(const Matrix4& m, float s) noexcept;
	Matrix4 operator/(const Matrix4& m, float s) noexcept;

	// Element-wise divide
	Matrix4 operator/(const Matrix4& m1, const Matrix4& m2) noexcept;

	//--------------------------------//
	// Color                          //
	//--------------------------------//
	struct Color final : DirectX::XMFLOAT4
	{
		explicit Color();

		explicit Color(float red, float green, float blue);

		explicit Color(float red, float green, float blue, float alpha);

		explicit Color(const Vector3Float& rgbColor);

		explicit Color(const XMFLOAT4& rgbaColor);

		~Color();

		[[nodiscard]]
		float Red() const;

		void Red(float red);

		[[nodiscard]]
		float Green() const;

		void Green(float green);

		[[nodiscard]]
		float Blue() const;

		void Blue(float blue);

		[[nodiscard]]
		float Alpha() const;

		void Alpha(float alpha);

		static Color Lerp(const Color& c1, const Color& c2, float t) noexcept;

		explicit operator DirectX::XMVECTOR() const;

		explicit operator float*() const;

		bool operator ==(const Color& c) const;

		bool operator !=(const Color& c) const;

		Color& operator+=(const Color& c);

		Color& operator-=(const Color& c);

		Color& operator*=(const Color& c);

		Color& operator*=(float s);

		Color& operator/=(const Color& c);

		Color operator+() const;

		Color operator-() const;

		Color(const Color&)            = default;
		Color& operator=(const Color&) = default;
		Color(Color&&)                 = default;
		Color& operator=(Color&&)      = default;

		friend std::ostream& operator<<(std::ostream& os, const Color& c);
	};

	Color operator+(const Color& c1, const Color& c2) noexcept;
	Color operator-(const Color& c1, const Color& c2) noexcept;
	Color operator*(const Color& c1, const Color& c2) noexcept;
	Color operator*(const Color& c, float s) noexcept;
	Color operator/(const Color& c1, const Color& c2) noexcept;
	std::ostream& operator<<(std::ostream& os, const Color& c);

	// TODO
	//--------------------------------//
	// Ray                            //
	//--------------------------------//

	// TODO
	//--------------------------------//
	// Viewport                       //
	//--------------------------------//
}
