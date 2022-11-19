#pragma once
#include "Engine/Math/Math.h"

#include "Engine/ECS/Core/Entity.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	class EditorCamera final : public Entity
	{
	public:
		explicit EditorCamera(EntityID id,
						StringView name,
						ComponentRegistry* componentRegistry);

		~EditorCamera() override;

		// Matrix4 ViewProjMatrix();
		//
		// void Update();
		//
		// float FoV = 45.0f;

		private:
		// void UpdateViewMatrix();
		//
		// void UpdateCameraVectors();
		//
		// TransformComponent* m_Transform;
		//
		// Matrix4 m_ViewMatrix;
		//
		// Matrix4 m_ProjMatrix;
		//
		// Vector3Float m_Front;
		//
		// Vector3Float m_Up;
		//
		// Vector3Float m_Right;
		//
		// Vector3Float m_WorldUp;
	};
}
