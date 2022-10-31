#pragma once

#include "Engine/Math/Matrix4.h"

#include "Entity.h"

#include "Engine/Math/Vector3.h"

namespace Engine
{
	class Camera : public Entity
	{
	public:
		explicit Camera(String name);

		~Camera() override;

		float FoV = 45.0f;

		Matrix4 ViewProjMatrix();

		void Update();

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

