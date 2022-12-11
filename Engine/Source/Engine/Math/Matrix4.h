#pragma once

namespace Engine
{
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

		static Matrix4 CreateFromAxisAngle(const Vector3Float& axis, float angle) noexcept;

		static Matrix4 CreateFromQuaternion(const Quaternion& quat) noexcept;

		static Matrix4 CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane,
		                                            float farPlane) noexcept;

		static Matrix4 CreatePerspective(float width, float height, float nearPlane, float farPlane) noexcept;

		static Matrix4 CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) noexcept;

		static Matrix4 CreateOrthographicOffCenter(float left, float right,
		                                           float bottom, float top,
		                                           float zNearPlane, float zFarPlane) noexcept;

		static Matrix4 CreateLookAt(Vector3Float position, Vector3Float target, Vector3Float up);

		static Matrix4 CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;

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
}
