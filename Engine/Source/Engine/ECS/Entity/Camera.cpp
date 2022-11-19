#include "pch.h"
#include "Camera.h"

#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Component/CameraComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Window.h"

namespace Engine
{
	Camera::Camera(const EntityID id,
	               const StringView name,
	               ComponentRegistry* componentRegistry,
	               uint64_t renderWidth,
	               uint64_t renderHeight) :
		Entity{id, name, componentRegistry}
	{
		auto transform = AttachComponent<TransformComponent>();
		AttachComponent<CameraComponent>(transform, renderWidth, renderHeight);
		//
		// m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		// m_Front   = Vector3Float(0.0f, 0.0f, -1.0f);
		// m_WorldUp = m_Up;
		// UpdateCameraVectors();
	}

	Camera::~Camera() = default;

	// Matrix4 Camera::ViewProjMatrix()
	// {
	// 	using namespace DirectX;
	// 	UpdateCameraVectors();
	// 	UpdateViewMatrix();
	//
	// 	const auto windowInfo = Application::GetWindowInfo();
	//
	// 	m_ProjMatrix = Matrix4::CreatePerspectiveFieldOfView(XMConvertToRadians(FoV),
	// 	                                                     (float)windowInfo.Width / (float)windowInfo.Height,
	// 	                                                     0.001f, 1000.0f);
	// 	m_ProjMatrix = m_ProjMatrix.Transpose();
	//
	// 	return m_ProjMatrix * m_ViewMatrix;
	// }
	//
	// void Camera::Update()
	// {
	// 	UpdateCameraVectors();
	// 	UpdateViewMatrix();
	// }
	//
	// void Camera::UpdateViewMatrix()
	// {
	// 	// m_ViewMatrix = Matrix4::CreateLookAt(m_Transform->Position,
	// 	//                                      m_Transform->Position + m_Front,
	// 	//                                      m_Up).Transpose();
	// }
	//
	// void Camera::UpdateCameraVectors()
	// {
	// 	float pitch = m_Transform->Rotation.x;
	// 	float yaw   = m_Transform->Rotation.y;
	// 	float roll  = m_Transform->Rotation.z;
	// 	
	// 	m_Front.x = std::cos(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
	// 	m_Front.y = std::sin(DegreesToRadians(pitch));
	// 	m_Front.z = std::sin(DegreesToRadians(yaw)) * std::cos(DegreesToRadians(pitch));
	// 	m_Front.Normalize();
	// 	
	// 	m_Right = m_Front.Cross(m_WorldUp);
	// 	m_Right.Normalize();
	// 	
	// 	m_Up = m_Right.Cross(m_Front);
	// 	m_Up.Normalize();
	// }
}
