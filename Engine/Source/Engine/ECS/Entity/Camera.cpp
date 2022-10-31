#include "pch.h"
#include "Camera.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	Camera::Camera(const String name) :
		Entity{name}
	{
		m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		m_Front   = Vector3Float(0.0f, 0.0f, -1.0f);
		m_WorldUp = m_Up;

		Transform().Rotation.x = 0;
		Transform().Rotation.y = -90.0f;

		UpdateCameraVectors();
	}

	Camera::~Camera()
	= default;

	Matrix4 Camera::ViewProjMatrix()
	{
		using namespace DirectX;
		UpdateCameraVectors();
		UpdateViewMatrix();

		m_ProjMatrix = Matrix4();
		auto rect    = Application::WindowRect();
		m_ProjMatrix *= Matrix4::CreatePerspectiveFieldOfView(XMConvertToRadians(FoV), (float)rect.Width / rect.Height,
		                                                      0.001f, 1000.0f);

		//m_ProjMatrix *= Matrix4::CreateOrthographic(rect.Width, rect.Height, -1000.0f, 1000.0f);
		//m_ProjMatrix *= Matrix4::CreatePerspectiveFieldOfView(45.0f, 1280.0f/1080.0f, 0.001f, 1000.0f);
		//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), -1000.0f, 1000.0f);
		//m_ProjMatrix *= XMMatrixOrthographicLH(1280, 1080, 0.001f, 1000.0f);
		//auto winSize = Application::WindowRef().GetSize();
		//m_ProjMatrix *= XMMatrixOrthographicLH(winSize.X(), winSize.Y(), 0.001f, 1000.0f);
		m_ProjMatrix = m_ProjMatrix.Transpose();

		return m_ProjMatrix * m_ViewMatrix;
	}

	void Camera::Update()
	{
		UpdateCameraVectors();
		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		m_ViewMatrix = Matrix4::CreateLookAt(m_Transform->Position,
		                                     m_Transform->Position + m_Front,
		                                     m_Up).Transpose();
	}

	void Camera::UpdateCameraVectors()
	{
		float pitch = Transform().Rotation.x;
		float yaw   = Transform().Rotation.y;
		float roll  = Transform().Rotation.z;

		m_Front.x = std::cos(DirectX::XMConvertToRadians(yaw)) * std::cos(DirectX::XMConvertToRadians(pitch));
		m_Front.y = std::sin(DirectX::XMConvertToRadians(pitch));
		m_Front.z = std::sin(DirectX::XMConvertToRadians(yaw)) * std::cos(DirectX::XMConvertToRadians(pitch));
		m_Front.Normalize();

		// TODO: Fix vector class to have static Cross()
		// TODO: Fix Normalize to have return normalized vector
		m_Right = m_Front.Cross(m_WorldUp);
		m_Right.Normalize();

		m_Up = m_Right.Cross(m_Front);
		m_Up.Normalize();
	}
}
