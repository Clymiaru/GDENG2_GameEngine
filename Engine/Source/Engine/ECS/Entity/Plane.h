#pragma once
#include "Entity.h"

#include "Engine/Math/Vector3.h"

namespace Engine
{
	class Camera;

	class RenderComponent;

	struct Constant;

	class Plane : public Entity
	{
	public:
		Plane(const String& name,
		      const Vector3Float& position);

		~Plane() override;

		void Update();

		void Draw(Camera& camera);

	private:
		RenderComponent* m_Render;
	};
}
