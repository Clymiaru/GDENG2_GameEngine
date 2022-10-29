#pragma once

#include "Engine/ECS/Entity/AEntity.h"

namespace Engine
{
	struct Constant;

	class Cube : public AEntity
	{
	public:
		Cube(const Vector3Float& position,
		     const Vector3Float& size,
		     const std::wstring& shaderName);

		~Cube() override;

		void Update(float deltaTime) override;

		void Draw() override;

	private:
		Constant* m_Constant;

		
		Primitive* m_Primitive;
	};
}
