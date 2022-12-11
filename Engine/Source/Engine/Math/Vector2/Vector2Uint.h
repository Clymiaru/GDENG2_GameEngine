#pragma once

namespace Engine
{
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

		//friend std::ostream& operator<<(std::ostream& os, const Vector2Uint& v);

		static Vector2Uint Zero;
		static Vector2Uint One;
	};

	Vector2Uint operator+(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator-(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator*(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator*(const Vector2Uint& v, float s);
	Vector2Uint operator/(const Vector2Uint& v1, const Vector2Uint& v2);
	Vector2Uint operator/(const Vector2Uint& v, float s);
	// std::ostream& operator<<(std::ostream& os, const Vector2Uint& v);
}
