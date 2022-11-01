#pragma once
#include "Entity.h"

#include "Engine/Math/Vector3.h"

namespace Engine
{
	class Camera;
	class RenderComponent;
	struct Constant;

	class Cube : public Entity
	{
	public:
		explicit Cube(const String& name,
		              const Vector3Float& position);

		~Cube() override;

		void Update();
		void Draw(Camera& camera);

	private:
		RenderComponent* m_Render;
	};
}
