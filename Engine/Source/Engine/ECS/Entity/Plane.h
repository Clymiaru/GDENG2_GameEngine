#pragma once
#include "Primitive.h"

#include "Engine/Core/AEntity.h"

namespace Engine
{
	struct Constant;

	class Plane : public AEntity
	{
	public:
		Plane(const Vector3& position,
		     const Vector3& size,
		     const std::wstring& shaderName);

		~Plane() override;

		void Update(float deltaTime) override;

		void Draw() override;

	private:
		Constant* m_Constant;

		Primitive* m_Primitive;
	};
}
