#pragma once
#include "Primitive.h"

#include "Engine/Core/Core.h"
#include "Engine/ECS/Entity/AEntity.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Vector2.h"

namespace Engine
{
	struct Constant;

	class Quad final : public AEntity
	{
	public:
		Quad(const Vector3Float& position,
		     const Vector2Float& size,
		     const Color& color,
		     const std::wstring& shaderName);

		~Quad() override;

		void Update(float deltaTime) override;

		void Draw() override;

	private:
		Color m_Color;

		Constant* m_Constant;

		Primitive* m_Primitive;
	};
}
