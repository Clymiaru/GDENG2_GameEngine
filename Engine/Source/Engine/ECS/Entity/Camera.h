#pragma once
#include "Engine/Math/Math.h"
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Camera : public Entity
	{
	public:
		explicit Camera(StringView name);

		~Camera() override;

		Matrix4 ViewProjMatrix();

		void Update();

		float FoV = 45.0f;

	private:
		void UpdateViewMatrix();

		void UpdateCameraVectors();

		Matrix4 m_ViewMatrix;

		Matrix4 m_ProjMatrix;

		Vector3Float m_Front;

		Vector3Float m_Up;

		Vector3Float m_Right;

		Vector3Float m_WorldUp;
	};
}
