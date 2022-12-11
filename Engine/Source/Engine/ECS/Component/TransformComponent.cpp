#include "pch.h"
#include "TransformComponent.h"

namespace Engine
{
	TransformComponent::TransformComponent(const EntityID& ownerID) :
		AComponent{ownerID},
		Position{Vector3Float::Zero},
		Scale{Vector3Float::One},
		Rotation{Vector3Float::Zero},
		m_Quaternion{Quaternion::Identity} { }

	TransformComponent::~TransformComponent() = default;

	Matrix4& TransformComponent::GetLocalMatrix()
	{
		RecalculateLocalMatrix();
		return m_LocalMatrix;
	}

	void TransformComponent::RecalculateLocalMatrix()
	{
		using namespace DirectX;
		m_LocalMatrix = Matrix4();

		// Apply Scale 
		m_LocalMatrix *= Matrix4::CreateScale(Scale);

		const float theta = std::sqrt(Rotation.x * Rotation.x +
		                              Rotation.y * Rotation.y +
		                              Rotation.z * Rotation.z) * 180.0f / PI;

		m_Quaternion = Quaternion::CreateFromYawPitchRoll(Rotation.y, Rotation.x, Rotation.z);
		
		m_LocalMatrix *= Matrix4::CreateFromQuaternion(m_Quaternion);
		
		// Apply Translation
		m_LocalMatrix *= Matrix4::CreateTranslation(Position);

		// Transpose for HLSL
		m_LocalMatrix = m_LocalMatrix.Transpose();
	}
}
