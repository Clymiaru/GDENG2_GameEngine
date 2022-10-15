#pragma once
#include <DirectXMath.h>

#include "Core.h"

namespace Engine
{
	class Vector2 final
	{
	public:
		Vector2() noexcept;

		constexpr explicit Vector2(const float x,
		                           const float y) noexcept;

		Vector2(const Vector2&) = default;

		Vector2& operator=(const Vector2&) = default;

		Vector2(Vector2&&) = default;

		Vector2& operator=(Vector2&&) = default;

		operator DirectX::XMVECTOR() const noexcept;

		bool operator ==(const Vector2& other) const noexcept;

		bool operator !=(const Vector2& other) const noexcept;

		Vector2& operator+=(const Vector2& other) noexcept;

		Vector2& operator-=(const Vector2& other) noexcept;

		Vector2& operator*=(float scalar) noexcept;

		Vector2& operator/=(float scalar) noexcept;

		Vector2 operator+() const noexcept;

		Vector2 operator-() const noexcept;

		[[nodiscard]]
		float Length() const noexcept;

		[[nodiscard]]
		float LengthSquared() const noexcept;

		[[nodiscard]]
		float Dot(const Vector2& other) const noexcept;

		[[nodiscard]]
		Vector2 Cross(const Vector2& other) const noexcept;

		void Normalize() noexcept;

		[[nodiscard]]
		Vector2 Normalize() const noexcept;

		//----------CONSTANTS
		static const Vector2 Zero;

		static const Vector2 One;

		static const Vector2 UnitX;

		static const Vector2 UnitY;

	private:
		DirectX::XMFLOAT2 m_Data;
	};

	Vector2 operator+(const Vector2& vector1,
	                  const Vector2& vector2) noexcept;

	Vector2 operator-(const Vector2& vector1,
	                  const Vector2& vector2) noexcept;

	Vector2 operator*(const Vector2& vector,
	                  float scalar) noexcept;

	Vector2 operator/(const Vector2& vector,
	                  float scalar) noexcept;

	class Vector3 final
	{
	public:
		Vector3() noexcept;

		constexpr explicit Vector3(const float x,
		                           const float y,
		                           const float z) noexcept;

		Vector3(const Vector3&) = default;

		Vector3& operator=(const Vector3&) = default;

		Vector3(Vector3&&) = default;

		Vector3& operator=(Vector3&&) = default;

		operator DirectX::XMVECTOR() const noexcept;

		bool operator ==(const Vector3& other) const noexcept;

		bool operator !=(const Vector3& other) const noexcept;

		Vector3& operator+=(const Vector3& other) noexcept;

		Vector3& operator-=(const Vector3& other) noexcept;

		Vector3& operator*=(float scalar) noexcept;

		Vector3& operator/=(float scalar) noexcept;

		Vector3 operator+() const noexcept;

		Vector3 operator-() const noexcept;

		[[nodiscard]]
		float Length() const noexcept;

		[[nodiscard]]
		float LengthSquared() const noexcept;

		[[nodiscard]]
		float Dot(const Vector3& other) const noexcept;

		[[nodiscard]]
		Vector3 Cross(const Vector3& other) const noexcept;

		void Normalize() noexcept;

		[[nodiscard]]
		Vector3 Normalize() const noexcept;

		//----------CONSTANTS
		static const Vector3 Zero;

		static const Vector3 One;

		static const Vector3 UnitX;

		static const Vector3 UnitY;

		static const Vector3 UnitZ;

		static const Vector3 Up;

		static const Vector3 Down;

		static const Vector3 Right;

		static const Vector3 Left;

		static const Vector3 Forward;

		static const Vector3 Backward;

	private:
		DirectX::XMFLOAT3 m_Data;
	};

	Vector3 operator+(const Vector3& vector1,
	                  const Vector3& vector2) noexcept;

	Vector3 operator-(const Vector3& vector1,
	                  const Vector3& vector2) noexcept;

	Vector3 operator*(const Vector3& vector,
	                  float scalar) noexcept;

	Vector3 operator/(const Vector3& vector,
	                  float scalar) noexcept;

	// Not sure yet
	// class Quaternion;

	class Matrix4x4;

	class Color
	{
	public:
		explicit Color() noexcept;

		constexpr explicit Color(float red,
		                         float green,
		                         float blue) noexcept;

		constexpr explicit Color(float red,
		                         float green,
		                         float blue,
		                         float alpha) noexcept;

		Color(const Color&) = default;

		Color& operator=(const Color&) = default;

		Color(Color&&) = default;

		Color& operator=(Color&&) = default;

		operator DirectX::XMVECTOR() const noexcept;

		bool operator ==(const Color& color) const noexcept;

		bool operator !=(const Color& color) const noexcept;

		Color& operator+=(const Color& color) noexcept;

		Color& operator-=(const Color& color) noexcept;

		Color& operator*=(const Color& color) noexcept;

		Color& operator*=(float scalar) noexcept;

		Color& operator/=(const Color& color) noexcept;

		Color operator+() const noexcept;

		Color operator-() const noexcept;

		float R() const noexcept;

		void R(float red) noexcept;

		float G() const noexcept;

		void G(float green) noexcept;

		float B() const noexcept;

		void B(float blue) noexcept;

		float A() const noexcept;

		void A(float alpha) noexcept;

		static Color Lerp(const Color& color1,
		                  const Color& color2,
		                  float ratio) noexcept;

	private:
		DirectX::XMFLOAT4 m_Data;
	};

	Color operator+(const Color& color1,
	                const Color& color2) noexcept;

	Color operator-(const Color& color1,
	                const Color& color2) noexcept;

	Color operator*(const Color& color1,
	                const Color& color2) noexcept;

	Color operator*(const Color& color,
	                float scalar) noexcept;

	Color operator/(const Color& color1,
	                const Color& color2) noexcept;

	class Viewport final
	{
	public:
		Viewport() noexcept :
			m_X(0.f),
			m_Y(0.f),
			m_Width(0.f),
			m_Height(0.f),
			m_MinDepth(0.f),
			m_MaxDepth(1.f)
		{
		}

		constexpr Viewport(const float x,
		                   const float y,
		                   const float width,
		                   const float height,
		                   const float minDepth = 0.f,
		                   const float maxDepth = 1.f) noexcept :
			m_X(x),
			m_Y(y),
			m_Width(width),
			m_Height(height),
			m_MinDepth(minDepth),
			m_MaxDepth(maxDepth)
		{
		}

		Viewport(const Viewport&) = default;

		Viewport& operator=(const Viewport&) = default;

		Viewport(Viewport&&) = default;

		Viewport& operator=(Viewport&&) = default;

		// Not sure yet
		// float AspectRatio() const noexcept;
		//
		// Vector3 Project(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world) const noexcept;
		// void Project(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world, Vector3& result) const noexcept;
		//
		// Vector3 Unproject(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world) const noexcept;
		// void Unproject(const Vector3& p, const Matrix& proj, const Matrix& view, const Matrix& world, Vector3& result) const noexcept;

	private:
		float m_X;

		float m_Y;

		float m_Width;

		float m_Height;

		float m_MinDepth;

		float m_MaxDepth;
	};
}
