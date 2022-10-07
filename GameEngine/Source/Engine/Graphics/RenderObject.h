#pragma once
#include <d3d11.h>

#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class VertexBuffer;

	struct IndexLayoutInfo
	{
		D3D11_INPUT_ELEMENT_DESC* Data;
		size_t Size;
	};

	class RenderObject
	{
	public:
		RenderObject();

		virtual ~RenderObject();

		auto Load(void* listOfVertices,
		          UINT vertexSize,
		          UINT listSize,
		          void* shaderByteCode,
		          UINT byteShaderSize) -> void;

		auto SetIndexLayout(D3D11_INPUT_ELEMENT_DESC* indexLayout,
		                    size_t indexLayoutSize) -> void;

	private:
		// Entity -> When we need reference to the one being rendered
		
		UniquePtr<VertexBuffer> m_VertexBuffer;

		D3D11_INPUT_ELEMENT_DESC* m_IndexLayoutDescription;

		size_t m_IndexLayoutDescriptionSize;
	};
}
