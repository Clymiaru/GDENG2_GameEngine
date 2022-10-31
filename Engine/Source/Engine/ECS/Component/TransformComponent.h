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

		Vector3Float Position;

		Vector3Float Scale;

		Vector3Float Rotation;
		
		Matrix4& LocalMatrix();

	private:
		void RecalculateLocalMatrix();

		Matrix4 m_LocalMatrix;
	};
}
