#pragma once
#include "Engine/Graphics/Core/IRenderable.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"

namespace Engine
{
	class Triangle final
	{
	public:
		Triangle(Vector3Float v1,
		         Vector3Float v2,
		         Vector3Float v3,
		         Color32 color);

		Triangle(Vector3Float v1,
				 Vector3Float v2,
				 Vector3Float v3,
				 Vector3Float nextV1,
				 Vector3Float nextV2,
				 Vector3Float nextV3,
				 Color32 color,
				 Color32 nextColor);

		auto Init(void* shaderByteCode,
		          UINT byteShaderSize) -> void;

		auto GetRenderable() -> const Ref<IRenderable>&;

		~Triangle();

	private:
		Ref<IRenderable> m_Renderable;

		Vector3Float m_V1;

		Vector3Float m_V2;

		Vector3Float m_V3;

		Vector3Float m_NextV1;

		Vector3Float m_NextV2;

		Vector3Float m_NextV3;

		Color32 m_Color;
		Color32 m_NextColor;
	};
}
