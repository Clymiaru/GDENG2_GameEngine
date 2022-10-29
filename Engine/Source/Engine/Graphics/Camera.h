#pragma once
#include "Engine/Math/Matrix4.h"
#include "Engine/Math/Vector3.h"

namespace Engine
{
	class Camera
	{
	public:
		~Camera() = default;
		static Camera& Instance();

		void Translate(const Vector3Float& amount);
		void Position(const Vector3Float& position);

		Matrix4 ViewProjMatrix();
		
	private:
		Camera() = default;
		Matrix4 m_ViewMatrix;
		Matrix4 m_ProjMatrix;
		Vector3Float m_Position = Vector3Float{0.0f, 0.0f, 0.0f};
	};
}
