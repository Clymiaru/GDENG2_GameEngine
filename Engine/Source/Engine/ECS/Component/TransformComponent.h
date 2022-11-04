#pragma once

#include "AComponent.h"

#include "Engine/Math/Math.h"

namespace Engine
{
	class TransformComponent final : AComponent
	{
	public:
		explicit TransformComponent(Entity& owner);
		~TransformComponent() override;

		MAKE_COMPONENT(Transform)
		
		Matrix4& LocalMatrix();

		Vector3Float Position;

		Vector3Float Scale;

		Vector3Float Rotation;

	private:
		void RecalculateLocalMatrix();

		Matrix4 m_LocalMatrix;
	};
}
