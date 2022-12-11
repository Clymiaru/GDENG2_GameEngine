#pragma once

namespace Engine
{
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

		//friend std::ostream& operator<<(std::ostream& os, const Vector3Uint& v);

		static Vector3Uint Zero;
		static Vector3Uint One;
	};

	Vector3Uint operator+(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator-(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator*(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator*(const Vector3Uint& v, float s);
	Vector3Uint operator/(const Vector3Uint& v1, const Vector3Uint& v2);
	Vector3Uint operator/(const Vector3Uint& v, float s);
	//std::ostream& operator<<(std::ostream& os, const Vector3Uint& v);
}
