#include "pch.h"
#include "TransformComponent.h"

namespace Engine
{
	TransformComponent::TransformComponent(const EntityID& ownerID) :
		AComponent{ownerID},
		Position{Vector3Float::Zero},
		Scale{Vector3Float::One},
		Rotation{Vector3Float::Zero}
	{
	}

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

		// Apply Rotation
		m_LocalMatrix *= Matrix4::CreateFromAxisAngle(Vector3Float(0, 1, 0), DegreesToRadians(Rotation.y));
		m_LocalMatrix *= Matrix4::CreateFromAxisAngle(Vector3Float(1, 0, 0), DegreesToRadians(Rotation.x));
		m_LocalMatrix *= Matrix4::CreateFromAxisAngle(Vector3Float(0, 0, 1), DegreesToRadians(Rotation.z));
		
		// Apply Translation
		m_LocalMatrix *= Matrix4::CreateTranslation(Position);

		// Transpose for HLSL
		m_LocalMatrix = m_LocalMatrix.Transpose();
	}
}
