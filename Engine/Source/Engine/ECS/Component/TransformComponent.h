#pragma once

#include "AComponent.h"

#include "Engine/Math/Math.h"

namespace Engine
{
	class TransformComponent final : AComponent
	{
	public:
		explicit TransformComponent(Entity* owner);
		~TransformComponent();
		
		void Position(const Vector3Float& newPosition);

		Vector3Float& Position();

		void Scale(const Vector3Float& newScale);

		Vector3Float& Scale();

		void Rotation(const Vector3Float& newRotation);

		Vector3Float& Rotation();

		Matrix4& LocalMatrix();

	private:
		void RecalculateLocalMatrix();
		
		Vector3Float m_Position;

		Vector3Float m_Scale;

		Vector3Float m_Rotation;

		Matrix4 m_LocalMatrix;
	};
}
