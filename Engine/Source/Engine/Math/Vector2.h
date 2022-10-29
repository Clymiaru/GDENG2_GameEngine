#pragma once
#include <DirectXMath.h>

namespace Engine
{
	// TODO: Make operator overload for printing to log
	//----------
	// Vector2Float
	//----------
	struct Vector2Float final : DirectX::XMFLOAT2
	{
		Vector2Float();

		explicit Vector2Float(float x,
		                      float y);

		explicit Vector2Float(const XMFLOAT2& v);

		~Vector2Float();

		Vector2Float(const Vector2Float&) = default;

		Vector2Float& operator=(const Vector2Float& v) = default;

		Vector2Float(Vector2Float&&) noexcept = default;

		Vector2Float& operator=(Vector2Float&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		bool operator ==(const Vector2Float& v) const;

		bool operator !=(const Vector2Float& v) const;

		Vector2Float& operator+=(const Vector2Float& v);

		Vector2Float& operator-=(const Vector2Float& v);

		Vector2Float& operator*=(const Vector2Float& v);

		Vector2Float& operator*=(float s);

		Vector2Float& operator/=(float s);

		Vector2Float operator+() const;

		Vector2Float operator-() const;

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
		static float Distance(const Vector2Float& v1,
		                      const Vector2Float& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Float& v1,
		                             const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Min(const Vector2Float& v1,
		                        const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Max(const Vector2Float& v1,
		                        const Vector2Float& v2);

		[[nodiscard]]
		static Vector2Float Lerp(const Vector2Float& v1,
		                         const Vector2Float& v2,
		                         float t);
	};

	Vector2Float operator+(const Vector2Float& v1,
	                       const Vector2Float& v2);

	Vector2Float operator-(const Vector2Float& v1,
	                       const Vector2Float& v2);

	Vector2Float operator*(const Vector2Float& v1,
	                       const Vector2Float& v2);

	Vector2Float operator*(const Vector2Float& v,
	                       float s);

	Vector2Float operator/(const Vector2Float& v1,
	                       const Vector2Float& v2);

	Vector2Float operator/(const Vector2Float& v,
	                       float s);

	//----------
	// Vector2Int
	//----------
	struct Vector2Int final : DirectX::XMINT2
	{
		Vector2Int();

		explicit Vector2Int(int32_t x,
		                    int32_t y);

		explicit Vector2Int(const XMINT2& v);

		~Vector2Int();

		Vector2Int(const Vector2Int&) = default;

		Vector2Int& operator=(const Vector2Int& v) = default;

		Vector2Int(Vector2Int&&) noexcept = default;

		Vector2Int& operator=(Vector2Int&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		bool operator ==(const Vector2Int& v) const;

		bool operator !=(const Vector2Int& v) const;

		Vector2Int& operator+=(const Vector2Int& v);

		Vector2Int& operator-=(const Vector2Int& v);

		Vector2Int& operator*=(const Vector2Int& v);

		Vector2Int& operator*=(float s);

		Vector2Int& operator/=(float s);
		
		Vector2Int operator+() const;

		Vector2Int operator-() const;

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
		static float Distance(const Vector2Int& v1,
		                      const Vector2Int& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Int& v1,
		                             const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Min(const Vector2Int& v1,
		                      const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Max(const Vector2Int& v1,
		                      const Vector2Int& v2);

		[[nodiscard]]
		static Vector2Int Lerp(const Vector2Int& v1,
		                       const Vector2Int& v2,
		                       float t);
	};

	Vector2Int operator+(const Vector2Int& v1,
	                     const Vector2Int& v2);

	Vector2Int operator-(const Vector2Int& v1,
	                     const Vector2Int& v2);

	Vector2Int operator*(const Vector2Int& v1,
	                     const Vector2Int& v2);

	Vector2Int operator*(const Vector2Int& v,
	                     float s);

	Vector2Int operator/(const Vector2Int& v1,
	                     const Vector2Int& v2);

	Vector2Int operator/(const Vector2Int& v,
	                     float s);

	//----------
	// Vector2Uint
	//----------
	struct Vector2Uint final : DirectX::XMUINT2
	{
		Vector2Uint();

		explicit Vector2Uint(uint32_t x,
		                     uint32_t y);

		explicit Vector2Uint(const XMUINT2& v);

		~Vector2Uint();

		Vector2Uint(const Vector2Uint&) = default;

		Vector2Uint& operator=(const Vector2Uint& v) = default;

		Vector2Uint(Vector2Uint&&) noexcept = default;

		Vector2Uint& operator=(Vector2Uint&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		bool operator ==(const Vector2Uint& v) const;

		bool operator !=(const Vector2Uint& v) const;

		Vector2Uint& operator+=(const Vector2Uint& v);

		Vector2Uint& operator-=(const Vector2Uint& v);

		Vector2Uint& operator*=(const Vector2Uint& v);

		Vector2Uint& operator*=(float s);

		Vector2Uint& operator/=(float s);

		Vector2Uint operator+() const;

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
		static float Distance(const Vector2Uint& v1,
		                      const Vector2Uint& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector2Uint& v1,
		                             const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Min(const Vector2Uint& v1,
		                       const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Max(const Vector2Uint& v1,
		                       const Vector2Uint& v2);

		[[nodiscard]]
		static Vector2Uint Lerp(const Vector2Uint& v1,
		                        const Vector2Uint& v2,
		                        float t);
	};

	Vector2Uint operator+(const Vector2Uint& v1,
	                      const Vector2Uint& v2);

	Vector2Uint operator-(const Vector2Uint& v1,
	                      const Vector2Uint& v2);

	Vector2Uint operator*(const Vector2Uint& v1,
	                      const Vector2Uint& v2);

	Vector2Uint operator*(const Vector2Uint& v,
	                      float s);

	Vector2Uint operator/(const Vector2Uint& v1,
	                      const Vector2Uint& v2);

	Vector2Uint operator/(const Vector2Uint& v,
	                      float s);
}
