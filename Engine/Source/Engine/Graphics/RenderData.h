#pragma once
#include <d3d11.h>

namespace Engine
{
	struct VertexData
	{
		void* VertexList;

		size_t VertexListCount;
	};

	struct VertexLayoutData
	{
		D3D11_INPUT_ELEMENT_DESC* VertexLayout;

		size_t VertexLayoutCount;
	};

	struct IndexData
	{
		uint32_t* IndexList;

		size_t IndexListCount;
	};
}