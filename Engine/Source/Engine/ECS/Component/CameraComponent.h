#pragma once
#include "Engine/Math/Math.h"
#include "Engine/ECS/Core/AComponent.h"

namespace Engine
{
	// Two ways to resolve dependencies:
	// One way is to intake a component reference
	// Another is to have the systems take care of dependencies (Go with this first)
		// Like the system won't update if a component is missing (must warn)
	
	class TransformComponent;
	class CameraComponent final : public AComponent
	{
	public:
		explicit CameraComponent(const EntityID& ownerID);

		~CameraComponent() override;

		MAKE_COMPONENT(Camera)
		
		Matrix4 GetViewProjMatrix(float aspectRatio);
		
		void Update(TransformComponent* transform);

	private:
		float FoV = 45.0f;

		void UpdateViewMatrix(TransformComponent* transform);

		void UpdateCameraVectors(TransformComponent* transform);
		
		Matrix4 m_ViewMatrix;

		Matrix4 m_ProjMatrix;

		Vector3Float m_Front;

		Vector3Float m_Up;

		Vector3Float m_Right;

		Vector3Float m_WorldUp;
	};
}
