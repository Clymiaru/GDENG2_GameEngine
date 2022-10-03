#pragma once
#include <d3d11.h>

namespace Engine
{
	class DeviceContext;

	class VertexBuffer final
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		[[nodiscard]]
		auto GetVertexListSize() const -> UINT;

		auto Load(void* listOfVertices,
		          UINT vertexSize,
		          UINT listSize,
		          void* shaderByteCode,
		          UINT byteShaderSize,
		          D3D11_INPUT_ELEMENT_DESC* indexLayout,
		          size_t indexLayoutSize) -> bool;

		auto Release() const -> void;

	private:
		UINT m_VertexSize;

		UINT m_ListSize;

		ID3D11Buffer* m_Buffer;

		ID3D11InputLayout* m_Layout;

		friend class DeviceContext;
	};
}
