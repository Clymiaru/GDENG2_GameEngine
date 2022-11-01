#pragma once
#include <DirectXMath.h>

namespace Engine
{
	// TODO: Make operator overload for printing to log

	
	//----------
	// Vector3Float
	//----------

	
	struct Vector3Float final : DirectX::XMFLOAT3
	{
		Vector3Float();

		explicit Vector3Float(float x,
		                      float y,
		                      float z);

		explicit Vector3Float(const XMFLOAT3& v);

		~Vector3Float();

		Vector3Float(const Vector3Float&) = default;

		Vector3Float& operator=(const Vector3Float& v) = default;

		Vector3Float(Vector3Float&&) noexcept = default;

		Vector3Float& operator=(Vector3Float&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		explicit operator float*() const { return (float*)(this); }

		bool operator ==(const Vector3Float& v) const;

		bool operator !=(const Vector3Float& v) const;

		Vector3Float& operator+=(const Vector3Float& v);

		Vector3Float& operator-=(const Vector3Float& v);

		Vector3Float& operator*=(const Vector3Float& v);

		Vector3Float& operator*=(float s);

		Vector3Float& operator/=(float s);

		Vector3Float operator+() const;

		Vector3Float operator-() const;

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
		static float Distance(const Vector3Float& v1,
		                      const Vector3Float& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Float& v1,
		                             const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Min(const Vector3Float& v1,
		                        const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Max(const Vector3Float& v1,
		                        const Vector3Float& v2);

		[[nodiscard]]
		static Vector3Float Lerp(const Vector3Float& v1,
		                         const Vector3Float& v2,
		                         float t);
	};

	Vector3Float operator+(const Vector3Float& v1,
	                       const Vector3Float& v2);

	Vector3Float operator-(const Vector3Float& v1,
	                       const Vector3Float& v2);

	Vector3Float operator*(const Vector3Float& v1,
	                       const Vector3Float& v2);

	Vector3Float operator*(const Vector3Float& v,
	                       float s);

	Vector3Float operator/(const Vector3Float& v1,
	                       const Vector3Float& v2);

	Vector3Float operator/(const Vector3Float& v,
	                       float s);

	//----------
	// Vector3Int
	//----------
	struct Vector3Int final : DirectX::XMINT3
	{
		Vector3Int();

		explicit Vector3Int(int32_t x,
		                    int32_t y,
		                    int32_t z);

		explicit Vector3Int(const XMINT3& v);

		~Vector3Int();

		Vector3Int(const Vector3Int&) = default;

		Vector3Int& operator=(const Vector3Int& v) = default;

		Vector3Int(Vector3Int&&) noexcept = default;

		Vector3Int& operator=(Vector3Int&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		bool operator ==(const Vector3Int& v) const;

		bool operator !=(const Vector3Int& v) const;

		Vector3Int& operator+=(const Vector3Int& v);

		Vector3Int& operator-=(const Vector3Int& v);

		Vector3Int& operator*=(const Vector3Int& v);

		Vector3Int& operator*=(float s);

		Vector3Int& operator/=(float s);
		
		Vector3Int operator+() const;

		Vector3Int operator-() const;

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
		static float Distance(const Vector3Int& v1,
		                      const Vector3Int& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Int& v1,
		                             const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Min(const Vector3Int& v1,
		                      const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Max(const Vector3Int& v1,
		                      const Vector3Int& v2);

		[[nodiscard]]
		static Vector3Int Lerp(const Vector3Int& v1,
		                       const Vector3Int& v2,
		                       float t);
	};

	Vector3Int operator+(const Vector3Int& v1,
	                     const Vector3Int& v2);

	Vector3Int operator-(const Vector3Int& v1,
	                     const Vector3Int& v2);

	Vector3Int operator*(const Vector3Int& v1,
	                     const Vector3Int& v2);

	Vector3Int operator*(const Vector3Int& v,
	                     float s);

	Vector3Int operator/(const Vector3Int& v1,
	                     const Vector3Int& v2);

	Vector3Int operator/(const Vector3Int& v,
	                     float s);

	//----------
	// Vector3Uint
	//----------
	struct Vector3Uint final : DirectX::XMUINT3
	{
		Vector3Uint();

		explicit Vector3Uint(uint32_t x,
		                     uint32_t y,
		                     uint32_t z);

		explicit Vector3Uint(const XMUINT3& v);

		~Vector3Uint();

		Vector3Uint(const Vector3Uint&) = default;

		Vector3Uint& operator=(const Vector3Uint& v) = default;

		Vector3Uint(Vector3Uint&&) noexcept = default;

		Vector3Uint& operator=(Vector3Uint&&) noexcept = default;

		explicit operator DirectX::XMVECTOR() const;

		bool operator ==(const Vector3Uint& v) const;

		bool operator !=(const Vector3Uint& v) const;

		Vector3Uint& operator+=(const Vector3Uint& v);

		Vector3Uint& operator-=(const Vector3Uint& v);

		Vector3Uint& operator*=(const Vector3Uint& v);

		Vector3Uint& operator*=(float s);

		Vector3Uint& operator/=(float s);

		Vector3Uint operator+() const;

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
		static float Distance(const Vector3Uint& v1,
		                      const Vector3Uint& v2);

		[[nodiscard]]
		static float DistanceSquared(const Vector3Uint& v1,
		                             const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Min(const Vector3Uint& v1,
		                       const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Max(const Vector3Uint& v1,
		                       const Vector3Uint& v2);

		[[nodiscard]]
		static Vector3Uint Lerp(const Vector3Uint& v1,
		                        const Vector3Uint& v2,
		                        float t);
	};

	Vector3Uint operator+(const Vector3Uint& v1,
	                      const Vector3Uint& v2);

	Vector3Uint operator-(const Vector3Uint& v1,
	                      const Vector3Uint& v2);

	Vector3Uint operator*(const Vector3Uint& v1,
	                      const Vector3Uint& v2);

	Vector3Uint operator*(const Vector3Uint& v,
	                      float s);

	Vector3Uint operator/(const Vector3Uint& v1,
	                      const Vector3Uint& v2);

	Vector3Uint operator/(const Vector3Uint& v,
	                      float s);
}

