#include "pch.h"
#include "TransformComponent.h"

namespace Engine
{
	TransformComponent::TransformComponent(Entity& owner) :
		AComponent{owner},
		Position{Vector3Float{0.0f, 0.0f, 0.0f}},
		Scale{Vector3Float{1.0f, 1.0f, 1.0f}},
		Rotation{Vector3Float{0.0f, 0.0f, 0.0f}}
	{
	}

	TransformComponent::~TransformComponent()
	{
		// Execute the parent's destructor last
		AComponent::~AComponent();
	}

	Matrix4& TransformComponent::LocalMatrix()
	{
		RecalculateLocalMatrix();
		return m_LocalMatrix;
	}

	void TransformComponent::RecalculateLocalMatrix()
	{
		using namespace DirectX;
		m_LocalMatrix = Matrix4();
		// Apply Rotation
		m_LocalMatrix *= Matrix4::CreateRotationX(XMConvertToRadians(Rotation.x));
		m_LocalMatrix *= Matrix4::CreateRotationY(XMConvertToRadians(Rotation.y));
		m_LocalMatrix *= Matrix4::CreateRotationZ(XMConvertToRadians(Rotation.z));

		// Apply Scale 
		m_LocalMatrix *= Matrix4::CreateScale(Scale);

		// Apply Translation
		m_LocalMatrix *= Matrix4::CreateTranslation(Position);

		// Transpose for HLSL
		m_LocalMatrix = m_LocalMatrix.Transpose();
	}
}
