#pragma once
#include "Engine/ECS/Core/Entity.h"

namespace Engine
{
	class Camera;
	class Plane final : public Entity
	{
	public:
		explicit Plane(StringView name);

		~Plane() override;

		void Draw(Camera& camera);
	};
}
