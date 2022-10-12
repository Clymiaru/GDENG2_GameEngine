#pragma once
#include <d3d11.h>

#include "Engine/Utils/Math.h"

namespace Engine
{
	class DeviceContext;

	class VertexBuffer final
	{
	public:
		VertexBuffer();

		~VertexBuffer();

		[[nodiscard]]
		Uint GetCount() const;

		[[nodiscard]]
		Uint GetSize() const;

		bool Load(const void* vertexList,
		          Uint vertexDataSize,
		          Uint vertexListCount,
		          const void* shaderByteCode,
		          Uint shaderByteCodeSize,
		          const D3D11_INPUT_ELEMENT_DESC* indexLayout,
		          Uint indexLayoutSize);

	private:
		ID3D11Buffer* m_Data;

		ID3D11InputLayout* m_DataLayout;

		UINT m_DataSize;

		UINT m_DataCount;

		friend class DeviceContext;
	};
}
