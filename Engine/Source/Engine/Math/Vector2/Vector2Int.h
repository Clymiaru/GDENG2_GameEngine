#pragma once

namespace Engine
{
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

		//friend std::ostream& operator<<(std::ostream& os, const Vector2Int& v);

		static Vector2Int Zero;
		static Vector2Int One;
	};

	Vector2Int operator+(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator*(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator*(const Vector2Int& v, float s);
	Vector2Int operator/(const Vector2Int& v1, const Vector2Int& v2);
	Vector2Int operator/(const Vector2Int& v, float s);
	//std::ostream& operator<<(std::ostream& os, const Vector2Int& v);
}
