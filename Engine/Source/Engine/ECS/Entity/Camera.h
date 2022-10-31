#pragma once
#include "Entity.h"

#include "Engine/Math/Matrix4.h"

namespace Engine
{
	class Camera : public Entity
	{
	public:
		Camera();

		~Camera() override;

		Matrix4 ViewProjMatrix();

	private:
		Matrix4 m_ProjMatrix;
	};	
}

