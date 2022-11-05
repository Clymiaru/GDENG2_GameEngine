#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Camera;
	class Cube final: public Entity
	{
	public:
		explicit Cube(StringView name);

		~Cube() override;

		void Draw(Camera& camera);
	};
}
