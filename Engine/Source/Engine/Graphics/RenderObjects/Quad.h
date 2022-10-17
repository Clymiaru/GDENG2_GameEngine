#pragma once
#include "Primitive.h"

#include "Engine/Core/AEntity.h"
#include "Engine/Core/Core.h"
#include "Engine/Core/Math.h"


namespace Engine
{
	struct Constant;

	class Quad final : public AEntity
	{
	public:
		Quad(const Vector3& position,
		     const Vector2& size,
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
