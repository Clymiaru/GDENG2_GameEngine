#include "pch.h"
#include "CameraComponent.h"

#include "TransformComponent.h"

namespace Engine
{
	CameraComponent::CameraComponent(const EntityID& ownerID) :
		AComponent{ownerID}
	{
		m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		m_Front   = Vector3Float(0.0f, 0.0f, -1.0f);
		m_WorldUp = m_Up;
	}

	CameraComponent::~CameraComponent() { }

	Matrix4 CameraComponent::GetViewProjMatrix(float aspectRatio)
	{
		m_ProjMatrix = Matrix4::CreatePerspectiveFieldOfView(DegreesToRadians(FoV),
		                                                     aspectRatio,
		                                                     0.001f, 1000.0f);
		m_ProjMatrix = m_ProjMatrix.Transpose();

		return m_ProjMatrix * m_ViewMatrix;
	}

	void CameraComponent::Update(TransformComponent* transform)
	{
		UpdateCameraVectors(transform);
		UpdateViewMatrix(transform);
	}

	void CameraComponent::UpdateViewMatrix(TransformComponent* transform)
	{
		m_ViewMatrix = Matrix4::CreateLookAt(transform->Position,
		                                     transform->Position + m_Front,
		                                     m_Up).Transpose();
	}

	void CameraComponent::UpdateCameraVectors(TransformComponent* transform)
	{
		float pitch = transform->Rotation.x;
		float yaw   = transform->Rotation.y;
		float roll  = transform->Rotation.z;

		m_Front.x = std::cos(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
		m_Front.y = std::sin(DegreesToRadians(pitch));
		m_Front.z = std::sin(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
		m_Front.Normalize();

		m_Right = m_Front.Cross(m_WorldUp);
		m_Right.Normalize();

		m_Up = m_Right.Cross(m_Front);
		m_Up.Normalize();
	}
}
