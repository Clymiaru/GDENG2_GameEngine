#include "pch.h"
#include "TransformComponent.h"

namespace Engine
{
	TransformComponent::TransformComponent(Entity* owner) :
		AComponent{owner},
		m_Position{Vector3Float{0.0f, 0.0f, 0.0f}},
		m_Scale{Vector3Float{1.0f, 1.0f, 1.0f}},
		m_Rotation{Vector3Float{0.0f, 0.0f, 0.0f}}
	{
	}

	TransformComponent::~TransformComponent()
	{
		// Execute the parent's destructor last
		AComponent::~AComponent();
	}

	void TransformComponent::Position(const Vector3Float& newPosition)
	{
		m_Position = newPosition;
		RecalculateLocalMatrix();
	}

	Vector3Float& TransformComponent::Position()
	{
		return m_Position;
	}

	void TransformComponent::Scale(const Vector3Float& newScale)
	{
		m_Scale = newScale;
		RecalculateLocalMatrix();
	}

	Vector3Float& TransformComponent::Scale()
	{
		return m_Scale;
	}

	void TransformComponent::Rotation(const Vector3Float& newRotation)
	{
		m_Rotation = newRotation;
		RecalculateLocalMatrix();
	}

	Vector3Float& TransformComponent::Rotation()
	{
		return m_Rotation;
	}

	Matrix4& TransformComponent::LocalMatrix()
	{
		return m_LocalMatrix;
	}

	void TransformComponent::RecalculateLocalMatrix()
	{
		using namespace DirectX;
		m_LocalMatrix = Matrix4();
		// Apply Rotation
		m_LocalMatrix *= Matrix4::CreateRotationX(XMConvertToRadians(m_Rotation.x));
		m_LocalMatrix *= Matrix4::CreateRotationY(XMConvertToRadians(m_Rotation.y));
		m_LocalMatrix *= Matrix4::CreateRotationZ(XMConvertToRadians(m_Rotation.z));

		// Apply Scale 
		m_LocalMatrix *= Matrix4::CreateScale(m_Scale);

		// Apply Translation
		m_LocalMatrix *= Matrix4::CreateTranslation(m_Position);

		// Transpose for HLSL
		m_LocalMatrix = m_LocalMatrix.Transpose();
	}
}
