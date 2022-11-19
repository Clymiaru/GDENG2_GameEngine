#include "pch.h"
#include "EditorCameraComponent.h"

#include "TransformComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Renderer.h"

namespace Engine
{
	EditorCameraComponent::EditorCameraComponent(const EntityID& ownerID,
	                                             SharedPtr<TransformComponent> transform) :
		AComponent{ownerID},
		m_Transform{transform}
	{
		m_Up      = Vector3Float(0.0f, 1.0f, 0.0f);
		m_Front   = Vector3Float(0.0f, 0.0f, -1.0f);
		m_WorldUp = m_Up;
	}

	EditorCameraComponent::~EditorCameraComponent() { }

	void EditorCameraComponent::SetSize(uint64_t width, uint64_t height)
	{
		const auto* storedFramebuffer = m_RenderTarget.release();
		delete storedFramebuffer;

		FramebufferProfile resizedFramebufferProfile;
		resizedFramebufferProfile.Width = width;
		resizedFramebufferProfile.Height = height;
		m_RenderTarget = Application::GetRenderer().GetDevice().CreateFramebuffer(resizedFramebufferProfile);
	}

	Matrix4 EditorCameraComponent::GetViewProjMatrix()
	{
		const float aspectRatio = (float)m_RenderTarget->GetInfo().Width / (float)m_RenderTarget->GetInfo().Height;
		
		m_ProjMatrix = Matrix4::CreatePerspectiveFieldOfView(DegreesToRadians(FoV),
		                                                     aspectRatio,
		                                                     0.001f, 1000.0f);
		m_ProjMatrix = m_ProjMatrix.Transpose();

		return m_ProjMatrix * m_ViewMatrix;
	}

	void EditorCameraComponent::Update()
	{
		UpdateCameraVectors();
		UpdateViewMatrix();
	}

	Framebuffer& EditorCameraComponent::GetRenderTarget() const
	{
		return *m_RenderTarget;
	}

	void EditorCameraComponent::UpdateViewMatrix()
	{
		m_ViewMatrix = Matrix4::CreateLookAt(m_Transform->Position,
		                                     m_Transform->Position + m_Front,
		                                     m_Up).Transpose();
	}

	void EditorCameraComponent::UpdateCameraVectors()
	{
		float pitch = m_Transform->Rotation.x;
		float yaw   = m_Transform->Rotation.y;
		float roll  = m_Transform->Rotation.z;

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
