#pragma once

#include "Engine/Graphics/ARenderObject.h"
#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	struct Constant;

	struct IndexLayoutInfo;

	class Quad final : public ARenderObject
	{
	public:
		Quad(const Vector3Float& position,
		     const Vector2Float& size,
		     const Color32& color);

		~Quad() override;

		auto Update(float deltaTime) -> void;

		auto Render() const -> void;

	private:
		Vector3Float m_Position;

		Vector2Float m_Size;

		Color32 m_Color;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;

		DirectX::XMMATRIX m_TransformMatrix;

		Constant* m_Constant;

		auto SetBuffers() -> void;

		auto InitializeVertexData() -> VertexData override;

		auto InitializeVertexLayout() -> VertexLayoutData override;

		auto InitializeIndexData() -> IndexData override;

		auto InitializeShaderData() -> void override;
	};
}
