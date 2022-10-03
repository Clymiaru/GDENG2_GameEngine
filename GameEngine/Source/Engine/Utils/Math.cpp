#include "pch.h"
#include "Math.h"

namespace Engine
{
	Mat4::Mat4() :
		m_Data(DirectX::XMMatrixIdentity())
	{
	}

	Mat4::~Mat4()
	{
	}

	auto Mat4::Translate(const Vector3Float& amount) -> void
	{
		m_Data = DirectX::XMMatrixTranslation(amount.X, amount.Y, amount.Z);
	}

	auto Mat4::SetOrthographicProjection(float width,
	                                     float height,
	                                     float nearPlane,
	                                     float farPlane) -> void
	{
		m_Data = DirectX::XMMatrixOrthographicLH(width, height, nearPlane, farPlane);
	}
}
