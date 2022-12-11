#pragma once
#include "Engine/Math/Math.h"
#include "Engine/ECS/Core/AComponent.h"

namespace Engine
{
	class TransformComponent final : public AComponent
	{
	public:
		explicit TransformComponent(const EntityID& ownerID);

		~TransformComponent() override;

		MAKE_COMPONENT(Transform)

		Matrix4& GetLocalMatrix();

		Vector3Float Position;

		Vector3Float Scale;

		Vector3Float Rotation;

		TransformComponent(const TransformComponent&)                = delete;
		TransformComponent& operator=(const TransformComponent&)     = delete;
		TransformComponent(TransformComponent&&) noexcept            = delete;
		TransformComponent& operator=(TransformComponent&&) noexcept = delete;

	private:
		void RecalculateLocalMatrix();

		Matrix4 m_LocalMatrix;
		Quaternion m_Quaternion;
		Vector3Float m_PrevRotation;
	};
}
