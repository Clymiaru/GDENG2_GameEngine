#pragma once

namespace Engine
{
	struct Matrix4;
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

		static Vector3Float Transform(const Vector3Float& v, const Matrix4& m);

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

		//friend std::ostream& operator<<(std::ostream& os, const Vector3Float& v);

		static Vector3Float Zero;
		static Vector3Float One;
	};

	Vector3Float operator+(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator-(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator*(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator*(const Vector3Float& v, float s);
	Vector3Float operator/(const Vector3Float& v1, const Vector3Float& v2);
	Vector3Float operator/(const Vector3Float& v, float s);
	//std::ostream& operator<<(std::ostream& os, const Vector3Float& v);
}