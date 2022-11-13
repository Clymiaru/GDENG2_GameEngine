#include "pch.h"
#include "TransformComponent.h"

namespace Engine
{
	TransformComponent::TransformComponent(Entity& owner) :
		AComponent{owner},
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
		
		// Apply Rotation
		m_LocalMatrix *= Matrix4::CreateRotationX(DegreesToRadians(Rotation.x));
		m_LocalMatrix *= Matrix4::CreateRotationY(DegreesToRadians(Rotation.y));
		m_LocalMatrix *= Matrix4::CreateRotationZ(DegreesToRadians(Rotation.z));

		// Apply Scale 
		m_LocalMatrix *= Matrix4::CreateScale(Scale);

		// Apply Translation
		m_LocalMatrix *= Matrix4::CreateTranslation(Position);

		// Transpose for HLSL
		m_LocalMatrix = m_LocalMatrix.Transpose();
	}
}
