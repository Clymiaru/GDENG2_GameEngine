#pragma once
#include <d3d11.h>

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
		Quad(const Vector2Float& position,
		     const Vector2Float& size,
		     const Color32& color);

		~Quad();

		auto Update(float deltaTime) -> void;


	private:
		struct Vertex
		{
			Vector3Float Position;

			Color32 Color;
		};

		Vector2Float m_Position;

		Vector2Float m_Size;

		Color32 m_Color;

		UniquePtr<ConstantBuffer> m_ConstantBuffer;

		DirectX::XMMATRIX m_ModelMat;

		Constant* constant;

		auto SetBuffers() -> void;

		auto InitializeVertexData() -> VertexData override;

		auto InitializeVertexLayout() -> VertexLayoutData override;

		auto InitializeIndexData() -> IndexData override;

		auto InitializeShaderData() -> void override;
	};
}
