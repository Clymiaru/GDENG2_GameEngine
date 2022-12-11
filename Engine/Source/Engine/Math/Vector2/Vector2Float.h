#pragma once

namespace Engine
{
	struct Vector2Float final : DirectX::XMFLOAT2
	{
		explicit Vector2Float();
		explicit Vector2Float(float x, float y);
		explicit Vector2Float(const XMFLOAT2& v);

		~Vector2Float();

		[[nodiscard]] float Length() const;
		[[nodiscard]] float LengthSquared() const;
		[[nodiscard]] float Dot(const Vector2Float& v) const;
		[[nodiscard]] Vector2Float Cross(const Vector2Float& v) const;

		void Normalize();

		[[nodiscard]] static float Distance(const Vector2Float& v1, const Vector2Float& v2);
		[[nodiscard]] static float DistanceSquared(const Vector2Float& v1, const Vector2Float& v2);
		[[nodiscard]] static Vector2Float Min(const Vector2Float& v1, const Vector2Float& v2);
		[[nodiscard]] static Vector2Float Max(const Vector2Float& v1, const Vector2Float& v2);
		[[nodiscard]] static Vector2Float Lerp(const Vector2Float& v1, const Vector2Float& v2, float t);

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

		//friend std::ostream& operator<<(std::ostream& os, const Vector2Float& v);

		static Vector2Float Zero;
		static Vector2Float One;
	};

	Vector2Float operator+(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator-(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator*(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator*(const Vector2Float& v, float s);
	Vector2Float operator/(const Vector2Float& v1, const Vector2Float& v2);
	Vector2Float operator/(const Vector2Float& v, float s);
	//std::ostream& operator<<(std::ostream& os, const Vector2Float& v);
}
