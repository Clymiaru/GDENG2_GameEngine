#pragma once
#include "Engine/Math/Math.h"
#include "Engine/ECS/Core/AComponent.h"

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

		TransformComponent(const TransformComponent&) = delete;
	
		TransformComponent& operator=(const TransformComponent&) = delete;
	
		TransformComponent(TransformComponent&&) noexcept = delete;
	
		TransformComponent& operator=(TransformComponent&&) noexcept = delete;

	private:
		void RecalculateLocalMatrix();

		Matrix4 m_LocalMatrix;
	};
}
