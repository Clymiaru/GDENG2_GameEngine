#include "pch.h"
#include "Quaternion.h"

namespace Engine
{
	const Quaternion Quaternion::Identity = Quaternion{ 0.f, 0.f, 0.f, 1.f };
	
	Quaternion::Quaternion() noexcept:
		XMFLOAT4(0, 0, 0, 1.f) {}

	Quaternion::Quaternion(float ix, float iy, float iz, float iw) noexcept:
		XMFLOAT4(ix, iy, iz, iw) {}
	
	Quaternion::Quaternion(const Vector3Float& v, float scalar) noexcept:
		XMFLOAT4(v.x, v.y, v.z, scalar) {}

	Quaternion::Quaternion(const XMFLOAT4& q) noexcept :
		XMFLOAT4{q} { }

	Quaternion::operator DirectX::XMVECTOR() const noexcept
	{
		return XMLoadFloat4(this);
	}

	bool Quaternion::operator ==(const Quaternion& q) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionEqual(q1, q2);
	}

	bool Quaternion::operator !=(const Quaternion& q) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionNotEqual(q1, q2);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& q) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorAdd(q1, q2));
		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& q) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorSubtract(q1, q2));
		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& q) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	Quaternion& Quaternion::operator*=(float S) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(q, S));
		return *this;
	}

	Quaternion& Quaternion::operator/=(const Quaternion& q) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2       = XMLoadFloat4(&q);
		q2                = XMQuaternionInverse(q2);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	Quaternion Quaternion::operator-() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);

		Quaternion R;
		XMStoreFloat4(&R, XMVectorNegate(q));
		return R;
	}

	Quaternion operator+(const Quaternion& Q1, const Quaternion& Q2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(&Q1);
		const XMVECTOR q2 = XMLoadFloat4(&Q2);

		Quaternion R;
		XMStoreFloat4(&R, XMVectorAdd(q1, q2));
		return R;
	}

	inline Quaternion operator-(const Quaternion& Q1, const Quaternion& Q2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(&Q1);
		const XMVECTOR q2 = XMLoadFloat4(&Q2);

		Quaternion R;
		XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
		return R;
	}

	Quaternion operator*(const Quaternion& Q1, const Quaternion& Q2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(&Q1);
		const XMVECTOR q2 = XMLoadFloat4(&Q2);

		Quaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	Quaternion operator*(const Quaternion& Q, float S) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(&Q);

		Quaternion R;
		XMStoreFloat4(&R, XMVectorScale(q, S));
		return R;
	}

	Quaternion operator/(const Quaternion& Q1, const Quaternion& Q2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2       = XMLoadFloat4(&Q2);
		q2                = XMQuaternionInverse(q2);

		Quaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	Quaternion operator*(float S, const Quaternion& Q) noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(&Q);

		Quaternion R;
		XMStoreFloat4(&R, XMVectorScale(q1, S));
		return R;
	}

	float Quaternion::Length() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLength(q));
	}

	float Quaternion::LengthSquared() const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLengthSq(q));
	}

	void Quaternion::Normalize() noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionNormalize(q));
	}

	void Quaternion::Conjugate() noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionConjugate(q));
	}

	inline void Quaternion::Inverse(Quaternion& result) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionInverse(q));
	}

	float Quaternion::Dot(const Quaternion& q) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR q1 = XMLoadFloat4(this);
		const XMVECTOR q2 = XMLoadFloat4(&q);
		return XMVectorGetX(XMQuaternionDot(q1, q2));
	}

	Quaternion Quaternion::RotateTowards(const Quaternion& target, float maxAngle) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR T = XMLoadFloat4(this);

		// We can use the conjugate here instead of inverse assuming q1 & q2 are normalized.
		const XMVECTOR R = XMQuaternionMultiply(XMQuaternionConjugate(T), (XMVECTOR)target);

		const float rs    = XMVectorGetW(R);
		const XMVECTOR L  = XMVector3Length(R);
		const float angle = 2.f * atan2f(XMVectorGetX(L), rs);

		Quaternion result;
		if (angle > maxAngle)
		{
			const XMVECTOR delta = XMQuaternionRotationAxis(R, maxAngle);
			const XMVECTOR Q     = XMQuaternionMultiply(delta, T);
			XMStoreFloat4(&result, Q);
		}
		else
		{
			// Don't overshoot.
			result = target;
		}
		return result;
	}

	Vector3Float Quaternion::ToEuler() const noexcept
	{
		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;

		const float m31 = 2.f * x * z + 2.f * y * w;
		const float m32 = 2.f * y * z - 2.f * x * w;
		const float m33 = 1.f - 2.f * xx - 2.f * yy;

		const float cy = sqrtf(m33 * m33 + m31 * m31);
		const float cx = atan2f(-m32, cy);
		if (cy > 16.f * FLT_EPSILON)
		{
			const float m12 = 2.f * x * y + 2.f * z * w;
			const float m22 = 1.f - 2.f * xx - 2.f * zz;

			return Vector3Float(cx, atan2f(m31, m33), atan2f(m12, m22));
		}
		else
		{
			const float m11 = 1.f - 2.f * yy - 2.f * zz;
			const float m21 = 2.f * x * y - 2.f * z * w;

			return Vector3Float(cx, 0.f, atan2f(-m21, m11));
		}
	}

	Quaternion Quaternion::CreateFromAxisAngle(const Vector3Float& axis, float angle) noexcept
	{
		using namespace DirectX;
		const XMVECTOR a = XMLoadFloat3(&axis);

		Quaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationAxis(a, angle));
		return R;
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept
	{
		using namespace DirectX;
		Quaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(const Vector3Float& angles) noexcept
	{
		using namespace DirectX;
		Quaternion R;
		const XMVECTOR a = XMLoadFloat3(&angles);
		XMStoreFloat4(&R, XMQuaternionRotationRollPitchYawFromVector(a));
		return R;
	}

	Quaternion Quaternion::CreateFromRotationMatrix(const Matrix4& M) noexcept
	{
		using namespace DirectX;
		const XMMATRIX M0 = XMLoadFloat4x4(&M);

		Quaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationMatrix(M0));
		return R;
	}

	Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		using namespace DirectX;
		const XMVECTOR Q0 = XMLoadFloat4(&q1);
		const XMVECTOR Q1 = XMLoadFloat4(&q2);

		const XMVECTOR dot = XMVector4Dot(Q0, Q1);

		XMVECTOR R;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
		{
			R = XMVectorLerp(Q0, Q1, t);
		}
		else
		{
			const XMVECTOR tv  = XMVectorReplicate(t);
			const XMVECTOR t1v = XMVectorReplicate(1.f - t);
			const XMVECTOR X0  = XMVectorMultiply(Q0, t1v);
			const XMVECTOR X1  = XMVectorMultiply(Q1, tv);
			R                  = XMVectorSubtract(X0, X1);
		}

		Quaternion result;
		XMStoreFloat4(&result, XMQuaternionNormalize(R));
		return result;
	}

	Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		using namespace DirectX;
		const XMVECTOR Q0 = XMLoadFloat4(&q1);
		const XMVECTOR Q1 = XMLoadFloat4(&q2);

		Quaternion result;
		XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
		return result;
	}

	float Quaternion::Angle(const Quaternion& q1, const Quaternion& q2) noexcept
	{
		using namespace DirectX;
		const XMVECTOR Q0 = XMLoadFloat4(&q1);
		const XMVECTOR Q1 = XMLoadFloat4(&q2);

		// We can use the conjugate here instead of inverse assuming q1 & q2 are normalized.
		XMVECTOR R = XMQuaternionMultiply(XMQuaternionConjugate(Q0), Q1);

		const float rs = XMVectorGetW(R);
		R              = XMVector3Length(R);
		return 2.f * atan2f(XMVectorGetX(R), rs);
	}
}
