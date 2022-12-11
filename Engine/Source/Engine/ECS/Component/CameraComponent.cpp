#include "pch.h"
#include "CameraComponent.h"

#include "TransformComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Graphics/Renderer.h"

namespace Engine
{
	CameraComponent::CameraComponent(const EntityID& ownerID,
	                                 SharedPtr<TransformComponent> transform,
	                                 uint32_t width,
	                                 uint32_t height) :
		AComponent{ownerID},
		ClearColor{0.5f, 0.3f, 0.8f, 1.0f},
		FoV{45.0f},
		OrthographicSize{5.0f},
		NearClipPlane{0.1f},
		FarClipPlane{1000.0f},
		Front{Vector3Float{0.0f, 0.0f, 1.0f}},
		Up{Vector3Float{0.0f, 1.0f, 0.0f}},
		Projection{Projection::Perspective},
		m_Transform{transform}
	{
		InitRenderTarget(width, height);
	}

	CameraComponent::~CameraComponent() = default;

	TransformComponent& CameraComponent::GetTransform() const
	{
		return *m_Transform;
	}

	void CameraComponent::UpdateViewMatrix(const Vector3Float& target, const Vector3Float& up)
	{
		m_ViewMatrix = Matrix4::CreateLookAt(m_Transform->Position,
		                                     target,
		                                     up);
	}

	void CameraComponent::SetSize(const uint32_t width, const uint32_t height)
	{
		const auto* storedFramebuffer = m_RenderTarget.release();
		delete storedFramebuffer;

		InitRenderTarget(width, height);
	}

	void CameraComponent::InitRenderTarget(const uint32_t width, const uint32_t height)
	{
		FramebufferProfile resizedFramebufferProfile;
		resizedFramebufferProfile.Width  = width;
		resizedFramebufferProfile.Height = height;

		m_RenderTarget = Application::GetRenderer().
		                 GetDevice().CreateFramebuffer(resizedFramebufferProfile);
	}

	void CameraComponent::SetPosition(const Vector3Float& position) const
	{
		m_Transform->Position = position;
	}

	void CameraComponent::SetRotation(const Vector3Float& rotation) const
	{
		m_Transform->Rotation = rotation;
	}

	const Vector3Float& CameraComponent::GetPosition() const
	{
		return m_Transform->Position;
	}

	const Vector3Float& CameraComponent::GetRotation() const
	{
		return m_Transform->Rotation;
	}

	Matrix4 CameraComponent::GetViewProjMatrix()
	{
		switch (Projection)
		{
			case Projection::Perspective:
			{
				const float width       = (float)m_RenderTarget->GetInfo().Width;
				const float height      = (float)m_RenderTarget->GetInfo().Height;
				const float aspectRatio = width / height;
				m_ProjMatrix            = Matrix4::CreatePerspectiveFieldOfView(DegreesToRadians(FoV),
				                                                                aspectRatio,
				                                                                NearClipPlane, FarClipPlane);
				break;
			}
			case Projection::Orthographic:
			{
				// TODO: Game viewport scale to resolution of the game camera
				const float height      = OrthographicSize;
				const float aspectRatio = 1.0f / ((float)m_RenderTarget->GetInfo().Width / height);
				const float width       = (float)m_RenderTarget->GetInfo().Width * aspectRatio;

				const float halfWidth  = width / 2.0f;
				const float halfHeight = height / 2.0f;

				const float left   = m_Transform->Position.x - halfWidth;
				const float right  = m_Transform->Position.x + halfWidth;
				const float top    = m_Transform->Position.y + halfHeight;
				const float bottom = m_Transform->Position.y - halfHeight;

				m_ProjMatrix = Matrix4::CreateOrthographicOffCenter(left, right,
				                                                    bottom, top,
				                                                    NearClipPlane, FarClipPlane);
				break;
			}
			default:
				break;
		}

		Matrix4 result = m_ViewMatrix * m_ProjMatrix;
		result         = result.Transpose();
		return result;
	}

	std::vector<DirectX::XMFLOAT4> CameraComponent::GetFrustumPlanes()
	{
		std::vector<DirectX::XMFLOAT4> tempFrustumPlane(6);

		DirectX::XMMATRIX viewProj = (DirectX::XMMATRIX)(m_ViewMatrix * m_ProjMatrix);
		tempFrustumPlane[0].x = viewProj.r[0].m128_f32[3] + viewProj.r[0].m128_f32[0];
		tempFrustumPlane[0].y = viewProj.r[1].m128_f32[3] + viewProj.r[1].m128_f32[0];
		tempFrustumPlane[0].z = viewProj.r[2].m128_f32[3] + viewProj.r[2].m128_f32[0];
		tempFrustumPlane[0].w = viewProj.r[3].m128_f32[3] + viewProj.r[3].m128_f32[0];

		tempFrustumPlane[1].x = viewProj.r[0].m128_f32[3] - viewProj.r[0].m128_f32[0];
		tempFrustumPlane[1].y = viewProj.r[1].m128_f32[3] - viewProj.r[1].m128_f32[0];
		tempFrustumPlane[1].z = viewProj.r[2].m128_f32[3] - viewProj.r[2].m128_f32[0];
		tempFrustumPlane[1].w = viewProj.r[3].m128_f32[3] - viewProj.r[3].m128_f32[0];

		tempFrustumPlane[2].x = viewProj.r[0].m128_f32[3] - viewProj.r[0].m128_f32[1];
		tempFrustumPlane[2].y = viewProj.r[1].m128_f32[3] - viewProj.r[1].m128_f32[1];
		tempFrustumPlane[2].z = viewProj.r[2].m128_f32[3] - viewProj.r[2].m128_f32[1];
		tempFrustumPlane[2].w = viewProj.r[3].m128_f32[3] - viewProj.r[3].m128_f32[1];

		tempFrustumPlane[3].x = viewProj.r[0].m128_f32[3] + viewProj.r[0].m128_f32[1];
		tempFrustumPlane[3].y = viewProj.r[1].m128_f32[3] + viewProj.r[1].m128_f32[1];
		tempFrustumPlane[3].z = viewProj.r[2].m128_f32[3] + viewProj.r[2].m128_f32[1];
		tempFrustumPlane[3].w = viewProj.r[3].m128_f32[3] + viewProj.r[3].m128_f32[1];

		tempFrustumPlane[4].x = viewProj.r[0].m128_f32[2];
		tempFrustumPlane[4].y = viewProj.r[1].m128_f32[2];
		tempFrustumPlane[4].z = viewProj.r[2].m128_f32[2];
		tempFrustumPlane[4].w = viewProj.r[3].m128_f32[2];

		tempFrustumPlane[5].x = viewProj.r[0].m128_f32[3] - viewProj.r[0].m128_f32[2];
		tempFrustumPlane[5].y = viewProj.r[1].m128_f32[3] - viewProj.r[1].m128_f32[2];
		tempFrustumPlane[5].z = viewProj.r[2].m128_f32[3] - viewProj.r[2].m128_f32[2];
		tempFrustumPlane[5].w = viewProj.r[3].m128_f32[3] - viewProj.r[3].m128_f32[2];

		for (int i = 0; i < 6; ++i)
		{
			float length = sqrt((tempFrustumPlane[i].x * tempFrustumPlane[i].x) + (tempFrustumPlane[i].y * tempFrustumPlane[i].y) + (tempFrustumPlane[i].z * tempFrustumPlane[i].z));
			tempFrustumPlane[i].x /= length;
			tempFrustumPlane[i].y /= length;
			tempFrustumPlane[i].z /= length;
			tempFrustumPlane[i].w /= length;
		}

		return tempFrustumPlane;
	}

	Framebuffer& CameraComponent::GetRenderTarget() const
	{
		return *m_RenderTarget;
	}
}
