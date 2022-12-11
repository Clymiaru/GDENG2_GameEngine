#pragma once

namespace Engine
{
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

		//friend std::ostream& operator<<(std::ostream& os, const Vector3Int& v);

		static Vector3Int Zero;
		static Vector3Int One;
	};

	Vector3Int operator+(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator-(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator*(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator*(const Vector3Int& v, float s);
	Vector3Int operator/(const Vector3Int& v1, const Vector3Int& v2);
	Vector3Int operator/(const Vector3Int& v, float s);
	//std::ostream& operator<<(std::ostream& os, const Vector3Int& v);
}